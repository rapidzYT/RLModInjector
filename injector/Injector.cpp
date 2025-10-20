#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

DWORD GetProcessId(const wchar_t* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32W);
        
        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                if (_wcsicmp(processEntry.szExeFile, processName) == 0) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }
    
    return processId;
}

bool InjectDLL(DWORD processId, const char* dllPath) {
    // Open target process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!hProcess) {
        std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
        return false;
    }
    
    // Allocate memory in target process
    size_t dllPathSize = strlen(dllPath) + 1;
    LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, dllPathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!pDllPath) {
        std::cerr << "Failed to allocate memory. Error: " << GetLastError() << std::endl;
        CloseHandle(hProcess);
        return false;
    }
    
    // Write DLL path to target process
    if (!WriteProcessMemory(hProcess, pDllPath, dllPath, dllPathSize, NULL)) {
        std::cerr << "Failed to write memory. Error: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }
    
    // Get address of LoadLibraryA
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    LPVOID pLoadLibrary = (LPVOID)GetProcAddress(hKernel32, "LoadLibraryA");
    
    // Create remote thread
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibrary, pDllPath, 0, NULL);
    if (!hThread) {
        std::cerr << "Failed to create remote thread. Error: " << GetLastError() << std::endl;
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }
    
    // Wait for thread to finish
    WaitForSingleObject(hThread, INFINITE);
    
    // Cleanup
    VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    
    return true;
}

int main(int argc, char* argv[]) {
    std::cout << "==================================" << std::endl;
    std::cout << "Rocket League TAS Mod Injector" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
    
    // Find Rocket League process
    std::wcout << L"Searching for Rocket League process..." << std::endl;
    DWORD processId = GetProcessId(L"RocketLeague.exe");
    
    if (processId == 0) {
        std::cerr << "Rocket League not found! Please start Rocket League first." << std::endl;
        std::cout << std::endl << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }
    
    std::cout << "Found Rocket League! Process ID: " << processId << std::endl;
    
    // Get DLL path
    char dllPath[MAX_PATH];
    GetFullPathNameA("RLTASMod.dll", MAX_PATH, dllPath, NULL);
    
    std::cout << "DLL Path: " << dllPath << std::endl;
    std::cout << std::endl;
    std::cout << "Injecting DLL..." << std::endl;
    
    // Inject DLL
    if (InjectDLL(processId, dllPath)) {
        std::cout << std::endl;
        std::cout << "SUCCESS! TAS Mod injected successfully!" << std::endl;
        std::cout << "Press F9 in Rocket League to toggle the TAS GUI." << std::endl;
    } else {
        std::cerr << std::endl;
        std::cerr << "FAILED! Could not inject DLL." << std::endl;
        std::cerr << "Make sure you're running as Administrator!" << std::endl;
    }
    
    std::cout << std::endl << "Press Enter to exit...";
    std::cin.get();
    return 0;
}
