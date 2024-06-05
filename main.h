

#pragma once
#include <windows.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <string>
#include <cctype>
#include <chrono>
#include <ctime>
#include <regex>
#include <math.h>

#include "misc/skstr.h"
#include "misc/helper.h"

#include "ui/roboto.h";
#include "ui/images.h"

#include <C:\Users\Cypher\Desktop\Include\d3dx9.h>
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"


#define load_name skCrypt("beamed.tech")
int window_width = 455; int window_height = 295;

ImFont* font;

UserData userD;

bool loader_active = true; bool user_profile = false; bool user_change = false;
HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }

}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
{
    return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
};

namespace Images {
    IDirect3DTexture9* imageExit = nullptr;
    IDirect3DTexture9* imageUser = nullptr;

    IDirect3DTexture9* imageDiscord = nullptr;
    IDirect3DTexture9* imageYoutube = nullptr;

    IDirect3DTexture9* imageDownload = nullptr;
    IDirect3DTexture9* imageStatus = nullptr;

    IDirect3DTexture9* imageLock = nullptr;
    IDirect3DTexture9* imageUnlock = nullptr;

    IDirect3DTexture9* imagePrivate2 = nullptr;

    IDirect3DTexture9* imageCheat = nullptr;

    IDirect3DTexture9* imageRename = nullptr;

    void Load() {
        if (imageExit == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &exit_, sizeof(exit_), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageExit);

        if (imageUser == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &user, sizeof(user), 64, 64, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageUser);

        if (imageDiscord == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &discord, sizeof(discord), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageDiscord);

        if (imageYoutube == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &youtube, sizeof(youtube), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageYoutube);

        if (imageCheat == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &fortnite2, sizeof(fortnite2), 32, 32, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageCheat);

        if (imageLock == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &lock, sizeof(lock), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageLock);

        if (imageUnlock == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &unlock, sizeof(unlock), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageUnlock);

        if (imageDownload == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &download, sizeof(download), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageDownload);

        if (imageStatus == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &info, sizeof(info), 16, 16, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageStatus);

        if (imageRename == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &spoofer, sizeof(spoofer), 32, 32, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &imageRename);
    }
}