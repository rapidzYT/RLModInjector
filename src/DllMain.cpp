#include "TASMod.h"
#include "D3D11Hook.h"
#include <Windows.h>
#include <thread>

using namespace RLTASMod;

static TASMod* g_TASMod = nullptr;
static D3D11Hook* g_D3D11Hook = nullptr;
static bool g_Running = false;

// Main thread for TAS mod
DWORD WINAPI MainThread(LPVOID lpParam) {
    // Wait for game to initialize
    Sleep(2000);
    
    // Create TAS mod instance
    g_TASMod = new TASMod();
    
    if (!g_TASMod->Initialize()) {
        MessageBoxA(NULL, "Failed to initialize TAS Mod", "Error", MB_OK | MB_ICONERROR);
        delete g_TASMod;
        g_TASMod = nullptr;
        return 0;
    }
    
    // Initialize D3D11 hook for rendering
    g_D3D11Hook = new D3D11Hook();
    if (!g_D3D11Hook->Initialize()) {
        MessageBoxA(NULL, "Failed to initialize D3D11 Hook", "Error", MB_OK | MB_ICONERROR);
        g_TASMod->Shutdown();
        delete g_TASMod;
        delete g_D3D11Hook;
        g_TASMod = nullptr;
        g_D3D11Hook = nullptr;
        return 0;
    }
    
    // Set render callback
    g_D3D11Hook->SetRenderCallback([](IDXGISwapChain* swapChain) {
        if (g_TASMod) {
            // Call OnFrame every frame to handle recording/replay
            g_TASMod->OnFrame();
            // Render the GUI
            g_TASMod->RenderGUI();
        }
    });
    
    g_Running = true;
    
    // Keep thread alive
    while (g_Running) {
        Sleep(100);
    }
    
    // Cleanup
    if (g_D3D11Hook) {
        g_D3D11Hook->Shutdown();
        delete g_D3D11Hook;
        g_D3D11Hook = nullptr;
    }
    
    if (g_TASMod) {
        g_TASMod->Shutdown();
        delete g_TASMod;
        g_TASMod = nullptr;
    }
    
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, MainThread, hModule, 0, NULL);
        break;
        
    case DLL_PROCESS_DETACH:
        g_Running = false;
        Sleep(200);
        break;
    }
    return TRUE;
}
