using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace RocketLeagueTAS.Injector
{
    public class DLLInjector
    {
        // Windows API functions for DLL injection
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        private static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        private static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool VirtualFreeEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint dwFreeType);

        private const int PROCESS_CREATE_THREAD = 0x0002;
        private const int PROCESS_QUERY_INFORMATION = 0x0400;
        private const int PROCESS_VM_OPERATION = 0x0008;
        private const int PROCESS_VM_WRITE = 0x0020;
        private const int PROCESS_VM_READ = 0x0010;
        private const uint MEM_COMMIT = 0x00001000;
        private const uint MEM_RESERVE = 0x00002000;
        private const uint PAGE_READWRITE = 4;
        private const uint INFINITE = 0xFFFFFFFF;
        private const uint MEM_RELEASE = 0x8000;

        public bool InjectDLL(string processName, string dllPath)
        {
            try
            {
                // Find the target process
                Process[] processes = Process.GetProcessesByName(processName);
                if (processes.Length == 0)
                {
                    Console.WriteLine($"Process '{processName}' not found!");
                    return false;
                }

                Process targetProcess = processes[0];
                Console.WriteLine($"Found process: {targetProcess.ProcessName} (PID: {targetProcess.Id})");

                // Check if DLL exists
                if (!File.Exists(dllPath))
                {
                    Console.WriteLine($"DLL not found: {dllPath}");
                    return false;
                }

                // Get full path to DLL
                string fullDllPath = Path.GetFullPath(dllPath);
                Console.WriteLine($"Injecting DLL: {fullDllPath}");

                // Open the target process
                IntPtr processHandle = OpenProcess(
                    PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,
                    false,
                    targetProcess.Id
                );

                if (processHandle == IntPtr.Zero)
                {
                    Console.WriteLine("Failed to open target process!");
                    return false;
                }

                try
                {
                    // Get the address of LoadLibraryA
                    IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
                    if (loadLibraryAddr == IntPtr.Zero)
                    {
                        Console.WriteLine("Failed to get LoadLibraryA address!");
                        return false;
                    }

                    // Allocate memory in the target process for the DLL path
                    IntPtr allocMemAddress = VirtualAllocEx(processHandle, IntPtr.Zero, (uint)((fullDllPath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                    if (allocMemAddress == IntPtr.Zero)
                    {
                        Console.WriteLine("Failed to allocate memory in target process!");
                        return false;
                    }

                    try
                    {
                        // Write the DLL path to the allocated memory
                        byte[] dllPathBytes = Encoding.ASCII.GetBytes(fullDllPath);
                        if (!WriteProcessMemory(processHandle, allocMemAddress, dllPathBytes, (uint)dllPathBytes.Length, out UIntPtr bytesWritten))
                        {
                            Console.WriteLine("Failed to write DLL path to target process!");
                            return false;
                        }

                        // Create a remote thread that calls LoadLibraryA with our DLL path
                        IntPtr threadHandle = CreateRemoteThread(processHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);
                        if (threadHandle == IntPtr.Zero)
                        {
                            Console.WriteLine("Failed to create remote thread!");
                            return false;
                        }

                        try
                        {
                            // Wait for the thread to complete
                            uint waitResult = WaitForSingleObject(threadHandle, INFINITE);
                            if (waitResult == 0)
                            {
                                Console.WriteLine("DLL injection successful!");
                                return true;
                            }
                            else
                            {
                                Console.WriteLine("Thread execution failed!");
                                return false;
                            }
                        }
                        finally
                        {
                            CloseHandle(threadHandle);
                        }
                    }
                    finally
                    {
                        VirtualFreeEx(processHandle, allocMemAddress, 0, MEM_RELEASE);
                    }
                }
                finally
                {
                    CloseHandle(processHandle);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"DLL injection failed: {ex.Message}");
                return false;
            }
        }

        public bool IsProcessRunning(string processName)
        {
            Process[] processes = Process.GetProcessesByName(processName);
            return processes.Length > 0;
        }

        public void WaitForProcess(string processName)
        {
            Console.WriteLine($"Waiting for {processName} to start...");
            while (!IsProcessRunning(processName))
            {
                System.Threading.Thread.Sleep(1000);
            }
            Console.WriteLine($"{processName} found!");
        }
    }
}