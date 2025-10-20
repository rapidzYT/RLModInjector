#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <functional>

namespace RLTASMod {

typedef void (*RenderCallback)(IDXGISwapChain* swapChain);

class D3D11Hook {
public:
    D3D11Hook();
    ~D3D11Hook();
    
    bool Initialize();
    void Shutdown();
    
    void SetRenderCallback(std::function<void(IDXGISwapChain*)> callback);
    
private:
    static HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    static HRESULT __stdcall ResizeBuffersHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
    
    bool HookPresent();
    void UnhookPresent();
    
    static void InitializeImGui(IDXGISwapChain* pSwapChain);
    static void ShutdownImGui();
    static void RenderImGui();
    
    static std::function<void(IDXGISwapChain*)> s_RenderCallback;
    static bool s_ImGuiInitialized;
    static ID3D11Device* s_Device;
    static ID3D11DeviceContext* s_Context;
    static ID3D11RenderTargetView* s_MainRenderTargetView;
    
    typedef HRESULT(__stdcall* PresentFn)(IDXGISwapChain*, UINT, UINT);
    typedef HRESULT(__stdcall* ResizeBuffersFn)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
    
    static PresentFn s_OriginalPresent;
    static ResizeBuffersFn s_OriginalResizeBuffers;
    
    bool hooked = false;
};

} // namespace RLTASMod
