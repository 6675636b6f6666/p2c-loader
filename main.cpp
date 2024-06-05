#include "main.h"

#include "ui/controls.h"
#include "ui/draw list.h"

#include "tabs/login.h"
#include "tabs/profile.h"
#include "tabs/main.h"



bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    // Render
    window->DrawList->PathClear();

    int num_segments = 30;
    int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

    const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
    const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

    const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

    for (int i = 0; i < num_segments; i++) {
        const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
        window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
            centre.y + ImSin(a + g.Time * 8) * radius));
    }

    window->DrawList->PathStroke(color, false, thickness);
}

void watchdog(){

    Sleep(8000);

    ExitProcess(0);



}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    RemoteLogin();

    if (auth::get_status() == skCrypt("success").decrypt()) {
        vars::validlogin = true;
    }
    else ExitProcess(0);


    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA(skCrypt("ConsoleWindowClass"), NULL);
    ShowWindow(Stealth, 0);

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, load_name, NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, load_name, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);


    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
       
    }

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(roboto, roboto_size, 14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(roboto, roboto_size, 17.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

    constexpr auto color_from_bytes = [](uint8_t r, uint8_t g, uint8_t b)
        {
            return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
        };

    ImGuiStyle* Style = &ImGui::GetStyle();
    Style->WindowBorderSize = 0.0;
    Style->FrameBorderSize = 0.0;
    Style->ChildBorderSize = 0.0;
    Style->WindowRounding = 0;
    Style->ChildRounding = 3;
    Style->FrameRounding = 3;
    Style->ScrollbarSize = 0;
    Style->WindowPadding = ImVec2(0, 0);
    Style->FramePadding = ImVec2(7, 7);
    Style->ItemSpacing = ImVec2(0, 0);
    Style->ItemInnerSpacing = ImVec2(0, 0);
    Style->IndentSpacing = 0;
    Style->DisplayWindowPadding = ImVec2(0, 0);

    Style->Colors[ImGuiCol_Border] = ImColor(54, 56, 71);
    Style->Colors[ImGuiCol_WindowBg] = ImColor(17, 19, 31);
    Style->Colors[ImGuiCol_ChildBg] = ImColor(11, 13, 25);
    Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
    Style->Colors[ImGuiCol_TextDisabled] = ImColor(53, 148, 247);
    Style->Colors[ImGuiCol_FrameBg] = ImColor(11, 13, 25);
    Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(3, 7, 19);
    Style->Colors[ImGuiCol_FrameBgActive] = ImColor(0, 0, 0);
    Style->Colors[ImGuiCol_Button] = ImColor(3, 7, 19);
    Style->Colors[ImGuiCol_ButtonHovered] = ImColor(11, 13, 25);
    Style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
    Style->Colors[ImGuiCol_CheckMark] = ImColor(54, 56, 71);

    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    DWORD window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - window_width) / 2.f;
    auto y = float(screen_rect.bottom - window_height) / 2.f;
    
    /*std::memset(vars::license, 0, sizeof(vars::license));

    userD.loadFromFile(skCrypt("C:\\ProgramData\\license.bin").decrypt());*/


    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {

            ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(window_width, window_height));
            ImGui::SetNextWindowBgAlpha(1.0f);

            ImGui::Begin(load_name, &loader_active, window_flags);
            {
                Images::Load();

                auto draw = ImGui::GetWindowDrawList();
                ImVec2 pos = ImGui::GetWindowPos();
                ImVec2 size = ImGui::GetWindowSize();

                vars::spinner_timer += ImGui::GetIO().DeltaTime;

                draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + 35), ImColor(3, 7, 19));      
                draw->AddText(font, 16, ImVec2(pos.x + 10, pos.y + 10), ImColor(255, 255, 255), load_name);

                ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 30, 8));
                if (Controls::ExitButton(skCrypt("##exit"), Images::imageExit, ImVec2(20, 20))) loader_active = false;

                if (vars::show_message_box)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, color_from_bytes(0, 0, 0));

                    ImVec2 textSize = ImGui::CalcTextSize(vars::message_box_message.c_str());
                    ImGui::SetNextWindowSize(ImVec2(textSize.x + 70, 70));

                    ImGui::OpenPopup(vars::message_box_title.c_str());

                    if (ImGui::BeginPopupModal(vars::message_box_title.c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, color_from_bytes(255, 255, 255));
                        ImGui::SetCursorPos(ImVec2(8, 33));
                        ImGui::LabelText(skCrypt("## %s"), vars::message_box_message.c_str(), vars::message_box_message);
                        ImGui::PopStyleColor();

                        ImGui::PushStyleColor(ImGuiCol_Text, color_from_bytes(255, 0, 0));

                        ImGui::SetCursorPos(ImVec2(8 + textSize.x + 17, 35));
                        if (ImGui::Button(skCrypt("OK"), ImVec2(30, 25)))
                        {
                            ImGui::CloseCurrentPopup();
                            vars::show_message_box = false;
                        }

                        ImGui::PopStyleColor();
                    }

                    ImGui::EndPopup();

                    ImGui::PopStyleColor();
                }

                if (vars::spinner_active2)
                {
                    ImGui::SetCursorPos(ImVec2(-1, 0));
                    ImGui::BeginChild(skCrypt("##spinner"), ImVec2(0, 0), true);
                    {
                        ImGui::SetCursorPos(ImVec2(125, 20));
                        Spinner(skCrypt("spinner"), 100.f, 1.f, ImColor(255, 255, 255));
                    }

                    ImGui::SetCursorPos(ImVec2(105, 260));
                    ImGui::SetWindowFontScale(1.3); // Increases the font size by scaling
                    ImGui::TextColored(ImColor(26, 255, 0), skCrypt("Loading your product, please wait...").decrypt());


                    ImGui::EndChild();

                   
                }

                if (vars::finaltab)
                {
                    
                    ImGui::SetCursorPos(ImVec2(-1, 0));
                    ImGui::BeginChild(skCrypt("##final"), ImVec2(0, 0), true);
                    ImGui::SetCursorPos(ImVec2(100, 140));
                    ImGui::SetWindowFontScale(1.5); // Increases the font size by scaling
                    ImGui::TextColored(ImColor(255, 0, 0), skCrypt("State -> Please launch Fortnite!").decrypt());
                    ImGui::EndChild();
                    std::thread(watchdog).detach();
                 
                }

                
                
                if (vars::validlogin = true) {
                    tabs::main_tab();
                }    
            }
            ImGui::End();

            if (user_profile) {
                tabs::user_tab();
            }
        }
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);


        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);

}

