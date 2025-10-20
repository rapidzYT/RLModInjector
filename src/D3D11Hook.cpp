#include "D3D11Hook.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "MinHook.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace RLTASMod {

// Static members
std::function<void(IDXGISwapChain*)> D3D11Hook::s_RenderCallback = nullptr;
bool D3D11Hook::s_ImGuiInitialized = false;
ID3D11Device* D3D11Hook::s_Device = nullptr;
ID3D11DeviceContext* D3D11Hook::s_Context = nullptr;
ID3D11RenderTargetView* D3D11Hook::s_MainRenderTargetView = nullptr;
D3D11Hook::PresentFn D3D11Hook::s_OriginalPresent = nullptr;
D3D11Hook::ResizeBuffersFn D3D11Hook::s_OriginalResizeBuffers = nullptr;

static WNDPROC oWndProc = nullptr;

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (D3D11Hook::s_ImGuiInitialized) {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        
        // Block input when GUI is visible
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
            return true;
        }
    }
    
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

D3D11Hook::D3D11Hook() {
}

D3D11Hook::~D3D11Hook() {
    Shutdown();
}

bool D3D11Hook::Initialize() {
    // Initialize MinHook
    if (MH_Initialize() != MH_OK) {
        return false;
    }
    
    return HookPresent();
}

void D3D11Hook::Shutdown() {
    UnhookPresent();
    ShutdownImGui();
    MH_Uninitialize();
}

void D3D11Hook::SetRenderCallback(std::function<void(IDXGISwapChain*)> callback) {
    s_RenderCallback = callback;
}

bool D3D11Hook::HookPresent() {
    // Create a temporary swap chain to get the vtable
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = GetForegroundWindow();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    
    IDXGISwapChain* pSwapChain = nullptr;
    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pContext = nullptr;
    
    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
        D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext))) {
        return false;
    }
    
    // Get the vtable
    void** pVTable = *reinterpret_cast<void***>(pSwapChain);
    
    // Hook Present (index 8)
    if (MH_CreateHook(pVTable[8], &PresentHook, reinterpret_cast<LPVOID*>(&s_OriginalPresent)) != MH_OK) {
        pSwapChain->Release();
        pDevice->Release();
        pContext->Release();
        return false;
    }
    
    // Hook ResizeBuffers (index 13)
    if (MH_CreateHook(pVTable[13], &ResizeBuffersHook, reinterpret_cast<LPVOID*>(&s_OriginalResizeBuffers)) != MH_OK) {
        pSwapChain->Release();
        pDevice->Release();
        pContext->Release();
        return false;
    }
    
    // Enable hooks
    MH_EnableHook(pVTable[8]);
    MH_EnableHook(pVTable[13]);
    
    pSwapChain->Release();
    pDevice->Release();
    pContext->Release();
    
    hooked = true;
    return true;
}

void D3D11Hook::UnhookPresent() {
    if (hooked) {
        MH_DisableHook(MH_ALL_HOOKS);
        hooked = false;
    }
}

HRESULT __stdcall D3D11Hook::PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    if (!s_ImGuiInitialized) {
        InitializeImGui(pSwapChain);
    }
    
    if (s_ImGuiInitialized) {
        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
        // Call render callback
        if (s_RenderCallback) {
            s_RenderCallback(pSwapChain);
        }
        
        // Render ImGui
        ImGui::Render();
        s_Context->OMSetRenderTargets(1, &s_MainRenderTargetView, NULL);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    
    return s_OriginalPresent(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall D3D11Hook::ResizeBuffersHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
    if (s_MainRenderTargetView) {
        s_MainRenderTargetView->Release();
        s_MainRenderTargetView = nullptr;
    }
    
    HRESULT hr = s_OriginalResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    
    if (s_Device && s_ImGuiInitialized) {
        ID3D11Texture2D* pBackBuffer = nullptr;
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if (pBackBuffer) {
            s_Device->CreateRenderTargetView(pBackBuffer, NULL, &s_MainRenderTargetView);
            pBackBuffer->Release();
        }
    }
    
    return hr;
}

void D3D11Hook::InitializeImGui(IDXGISwapChain* pSwapChain) {
    if (s_ImGuiInitialized) return;
    
    // Get device and context
    pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&s_Device);
    s_Device->GetImmediateContext(&s_Context);
    
    // Get window handle
    DXGI_SWAP_CHAIN_DESC desc;
    pSwapChain->GetDesc(&desc);
    HWND hWnd = desc.OutputWindow;
    
    // Hook window proc
    oWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProcHook);
    
    // Create render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (pBackBuffer) {
        s_Device->CreateRenderTargetView(pBackBuffer, NULL, &s_MainRenderTargetView);
        pBackBuffer->Release();
    }
    
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Setup ImGui style
    ImGui::StyleColorsDark();
    
    // Initialize ImGui backends
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(s_Device, s_Context);
    
    s_ImGuiInitialized = true;
}

void D3D11Hook::ShutdownImGui() {
    if (!s_ImGuiInitialized) return;
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    
    if (s_MainRenderTargetView) {
        s_MainRenderTargetView->Release();
        s_MainRenderTargetView = nullptr;
    }
    
    if (s_Context) {
        s_Context->Release();
        s_Context = nullptr;
    }
    
    if (s_Device) {
        s_Device->Release();
        s_Device = nullptr;
    }
    
    s_ImGuiInitialized = false;
}

} // namespace RLTASMod
