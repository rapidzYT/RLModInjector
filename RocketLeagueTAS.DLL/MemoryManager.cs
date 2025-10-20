using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace RocketLeagueTAS.DLL
{
    public class MemoryManager
    {
        private Process targetProcess;
        private IntPtr processHandle;
        private IntPtr carPositionPtr;
        private IntPtr carRotationPtr;
        private IntPtr carVelocityPtr;
        private IntPtr carAngularVelocityPtr;
        private IntPtr ballPositionPtr;
        private IntPtr ballVelocityPtr;
        private IntPtr ballAngularVelocityPtr;

        // Windows API functions for memory manipulation
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll")]
        private static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll")]
        private static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        private static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll")]
        private static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll")]
        private static extern bool VirtualFreeEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint dwFreeType);

        private const int PROCESS_ALL_ACCESS = 0x1F0FFF;
        private const uint MEM_COMMIT = 0x1000;
        private const uint MEM_RESERVE = 0x2000;
        private const uint PAGE_READWRITE = 0x04;

        // Rocket League memory offsets (these would need to be updated for different game versions)
        private const long CAR_POSITION_OFFSET = 0x01C8F2E8;
        private const long CAR_ROTATION_OFFSET = 0x01C8F2F4;
        private const long CAR_VELOCITY_OFFSET = 0x01C8F300;
        private const long CAR_ANGULAR_VELOCITY_OFFSET = 0x01C8F30C;
        private const long BALL_POSITION_OFFSET = 0x01C8F318;
        private const long BALL_VELOCITY_OFFSET = 0x01C8F324;
        private const long BALL_ANGULAR_VELOCITY_OFFSET = 0x01C8F330;

        public void Initialize(Process process)
        {
            targetProcess = process;
            processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, process.Id);
            
            if (processHandle == IntPtr.Zero)
            {
                throw new Exception("Failed to open Rocket League process");
            }

            // Calculate memory addresses (base address + offset)
            IntPtr baseAddress = process.MainModule.BaseAddress;
            carPositionPtr = new IntPtr(baseAddress.ToInt64() + CAR_POSITION_OFFSET);
            carRotationPtr = new IntPtr(baseAddress.ToInt64() + CAR_ROTATION_OFFSET);
            carVelocityPtr = new IntPtr(baseAddress.ToInt64() + CAR_VELOCITY_OFFSET);
            carAngularVelocityPtr = new IntPtr(baseAddress.ToInt64() + CAR_ANGULAR_VELOCITY_OFFSET);
            ballPositionPtr = new IntPtr(baseAddress.ToInt64() + BALL_POSITION_OFFSET);
            ballVelocityPtr = new IntPtr(baseAddress.ToInt64() + BALL_VELOCITY_OFFSET);
            ballAngularVelocityPtr = new IntPtr(baseAddress.ToInt64() + BALL_ANGULAR_VELOCITY_OFFSET);

            Console.WriteLine("Memory manager initialized successfully");
        }

        public Vector3 GetCarPosition()
        {
            return ReadVector3(carPositionPtr);
        }

        public void SetCarPosition(Vector3 position)
        {
            WriteVector3(carPositionPtr, position);
        }

        public Vector3 GetCarRotation()
        {
            return ReadVector3(carRotationPtr);
        }

        public void SetCarRotation(Vector3 rotation)
        {
            WriteVector3(carRotationPtr, rotation);
        }

        public Vector3 GetCarVelocity()
        {
            return ReadVector3(carVelocityPtr);
        }

        public void SetCarVelocity(Vector3 velocity)
        {
            WriteVector3(carVelocityPtr, velocity);
        }

        public Vector3 GetCarAngularVelocity()
        {
            return ReadVector3(carAngularVelocityPtr);
        }

        public void SetCarAngularVelocity(Vector3 angularVelocity)
        {
            WriteVector3(carAngularVelocityPtr, angularVelocity);
        }

        public Vector3 GetBallPosition()
        {
            return ReadVector3(ballPositionPtr);
        }

        public void SetBallPosition(Vector3 position)
        {
            WriteVector3(ballPositionPtr, position);
        }

        public Vector3 GetBallVelocity()
        {
            return ReadVector3(ballVelocityPtr);
        }

        public void SetBallVelocity(Vector3 velocity)
        {
            WriteVector3(ballVelocityPtr, velocity);
        }

        public Vector3 GetBallAngularVelocity()
        {
            return ReadVector3(ballAngularVelocityPtr);
        }

        public void SetBallAngularVelocity(Vector3 angularVelocity)
        {
            WriteVector3(ballAngularVelocityPtr, angularVelocity);
        }

        private Vector3 ReadVector3(IntPtr address)
        {
            byte[] buffer = new byte[12]; // 3 floats = 12 bytes
            if (ReadProcessMemory(processHandle, address, buffer, 12, out int bytesRead))
            {
                return new Vector3
                {
                    X = BitConverter.ToSingle(buffer, 0),
                    Y = BitConverter.ToSingle(buffer, 4),
                    Z = BitConverter.ToSingle(buffer, 8)
                };
            }
            return new Vector3();
        }

        private void WriteVector3(IntPtr address, Vector3 vector)
        {
            byte[] buffer = new byte[12];
            BitConverter.GetBytes(vector.X).CopyTo(buffer, 0);
            BitConverter.GetBytes(vector.Y).CopyTo(buffer, 4);
            BitConverter.GetBytes(vector.Z).CopyTo(buffer, 8);

            WriteProcessMemory(processHandle, address, buffer, 12, out int bytesWritten);
        }

        public void Dispose()
        {
            if (processHandle != IntPtr.Zero)
            {
                CloseHandle(processHandle);
                processHandle = IntPtr.Zero;
            }
        }

        ~MemoryManager()
        {
            Dispose();
        }
    }
}