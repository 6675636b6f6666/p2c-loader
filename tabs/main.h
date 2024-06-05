

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "../misc/injector.h"
//#pragma comment(lib, "mapper.lib")
#include <thread>

namespace mapper {

    void execute(std::vector<std::uint8_t> bytes);

}

std::vector<std::uint8_t> filestream(std::string name, std::string secret, std::string hash);

std::vector<std::uint8_t> fixpe(const std::vector<std::uint8_t>& originalVector) {
    // Make sure the vector has at least 2 bytes
    if (originalVector.size() < 2) {
        // Handle the case where the vector is too small
        // Return the original vector or an empty vector based on your requirements
        return originalVector;
    }

    // Create a new vector by erasing the first 2 bytes
    std::vector<std::uint8_t> modifiedVector(originalVector.begin() + 2, originalVector.end());

    return modifiedVector;
}

DWORD process_ID(const wchar_t* process)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, procId);

    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32FirstW(hSnap, &procEntry)) {
            do {
                if (wcscmp(process, procEntry.szExeFile) == 0) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

bool done = false;

void runclient() {


    /*std::vector<std::uint8_t> fakedrv = filestream(skCrypt("nvtO6gY5").decrypt(), skCrypt("32e23lewcwf").decrypt(), skCrypt("ba0196b8aa9fb8dd85dc988149e2971a97ab684e8d64c64dae5a09379aed17ca").decrypt());

    std::vector<std::uint8_t> driver = fixpe(fakedrv);

    mapper::execute(driver);*/

    std::vector<std::uint8_t> fakedll = filestream(skCrypt("DCgycNg7").decrypt(), skCrypt("dwedf3wf23f").decrypt(), skCrypt("ba0196b8aa9fb8dd85dc988149e2971a97ab684e8d64c64dae5a09379aed17ca").decrypt());

    std::vector<std::uint8_t> dll = fixpe(fakedll);

    DWORD TaskPid = process_ID(skCrypt(L"Overwolf.exe").decrypt());
    HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, 0, TaskPid);

    if (TaskPid)
    {

        if (!ManualMapDll(hproc, (BYTE*)&dll[0], dll.size(), true, true, true, true, DLL_PROCESS_ATTACH, 0))
        {
            MessageBoxA(NULL, skCrypt("Please open Overwolf as admin!").decrypt(), skCrypt("Error").decrypt(), MB_ICONERROR);
            exit(0);
        }
    }

   /* RtlSecureZeroMemory(&fakedrv, sizeof(fakedrv));
    RtlSecureZeroMemory(&driver, sizeof(driver));*/
    RtlSecureZeroMemory(&fakedll, sizeof(fakedll));
    RtlSecureZeroMemory(&dll, sizeof(dll));

    Sleep(5000);

    vars::spinner_active2 = false;

    vars::finaltab = true;


}

std::string getSubscriptionCountdown(const std::tm& expirationDate) {
    // Get the current time
    auto currentTime = std::chrono::system_clock::now();

    // Convert expiration date to time_point
    std::chrono::system_clock::time_point expirationTime = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&expirationDate)));

    // Calculate the duration remaining until expiration
    auto remainingTime = std::chrono::duration_cast<std::chrono::seconds>(expirationTime - currentTime);

    // Calculate hours, minutes, and seconds
    int days = std::chrono::duration_cast<std::chrono::hours>(remainingTime).count() / 24;
    int hours = std::chrono::duration_cast<std::chrono::hours>(remainingTime).count() % 24;
    int minutes = std::chrono::duration_cast<std::chrono::minutes>(remainingTime % std::chrono::hours(1)).count();
    int seconds = std::chrono::duration_cast<std::chrono::seconds>(remainingTime % std::chrono::minutes(1)).count();

    // Format the countdown as a string
    std::ostringstream countdown;
    countdown << days << "d " << hours << "h " << minutes << "min " << seconds << "s";

    return countdown.str();
}

bool final = false;

namespace tabs {
    void main_tab() {


        static bool showImGuiFrame = true;

        // Use the flag to conditionally render the ImGui frame
        if (showImGuiFrame) {

            window_width = 455; window_height = 295;

            DrawList::Text(skCrypt("txt5"), skCrypt("Products"), ImGui::GetFont(), 14, ImVec2(15, 45), ImColor(54, 56, 71));
            DrawList::Text(skCrypt("txt6"), skCrypt("USER INFORMATION"), ImGui::GetFont(), 14, ImVec2(260, 45), ImColor(54, 56, 71));

            ImGui::SetCursorPos(ImVec2(15, 65));
            ImGui::BeginChild(skCrypt("##cheats"), ImVec2(230, 195), false);

            const char* sub = skCrypt("");
            const char* nosub = skCrypt("");

            /* std::string subname = BitSync::get_subname().c_str();

             if (subname == skCrypt("Flyside.ggg").decrypt()) {

                 vars::cheat1 = true;
                 vars::cheat3 = true;

             }

             else if (subname == skCrypt("Kegel").decrypt()) {

                 vars::cheat2 = true;
                 vars::cheat3 = true;

             }*/

            vars::cheat1 = true;

            ImGui::SetCursorPos(ImVec2(0, 0));
            if (Controls::CheatButton(skCrypt("FORTNITE PUBLIC"), vars::cheat1 ? sub : nosub, Images::imageCheat, vars::cheat1 ? Images::imageUnlock : Images::imageLock, vars::selected_cheat == 0, ImVec2(230, 48))) {
                if (vars::cheat1) { vars::can_inject = true; }
                else if (!vars::cheat1) { vars::can_inject = false; }
                vars::selected_cheat = 0;
            }

            /* ImGui::SetCursorPos(ImVec2(0, 48));
             if (Controls::CheatButton(skCrypt("FORTNITE PRIVATE"), vars::cheat2 ? sub : nosub, Images::imageCheat, vars::cheat2 ? Images::imageUnlock : Images::imageLock, vars::selected_cheat == 1, ImVec2(230, 48))) {
                 if (vars::cheat2) { vars::can_inject = true; } else if (!vars::cheat2) { vars::can_inject = false; }
                 vars::selected_cheat = 1;
             }*/

            ImGui::SetCursorPos(ImVec2(0, 48));
            if (Controls::CheatButton(skCrypt("SPOOFER"), vars::cheat3 ? sub : nosub, Images::imageRename, vars::cheat3 ? Images::imageUnlock : Images::imageLock, vars::selected_cheat == 2, ImVec2(230, 48))) {
                if (vars::cheat3) { vars::can_inject = true; }
                else if (!vars::cheat3) { vars::can_inject = false; }
                vars::selected_cheat = 2;
            }

            /*ImGui::SetCursorPos(ImVec2(0, 96));
            if (Controls::CheatButton(skCrypt("SPOOFER"), vars::cheat3 ? sub : nosub, Images::imageRename, vars::cheat3 ? Images::imageUnlock : Images::imageLock, vars::selected_cheat == 2, ImVec2(230, 48))) {
                if (vars::cheat3) { vars::can_inject = true; } else if (!vars::cheat3) { vars::can_inject = false; }
                vars::selected_cheat = 2;
            }*/

            ImGui::EndChild();

            ImGui::SetCursorPos(ImVec2(260, 65));
            ImGui::BeginChild(skCrypt("##user"), ImVec2(180, 150), false);

            ImGui::SetCursorPos(ImVec2(58, 15));
            ImGui::Image(Images::imageUser, ImVec2(64, 64));

            std::string username = auth::get_username();

            ImGui::SetCursorPosY(95);
            DrawList::TextCentered(username.c_str());

            ImGui::PushStyleColor(ImGuiCol_Text, ColorFromBytes(53, 148, 247));

            ImGui::SetCursorPosY(115);
            DrawList::TextCentered(user_information::sub);

            ImGui::PopStyleColor();

            ImGui::EndChild();

            static float progress = 0.0f;
            static bool loading = false;

            ImGui::SetCursorPos(ImVec2(260, 230));
            if (Controls::InjectButton(skCrypt("LAUNCH"), Images::imageDownload, ImVec2(83, 30), vars::can_inject)) {

                if (vars::selected_cheat == 0) {

                    showImGuiFrame = false;

                    vars::spinner_timer = -2.0f; vars::spinner_active2 = true;

                    std::thread(runclient).detach();

                   

                }
                else if (vars::selected_cheat == 1) {

                }
                else if (vars::selected_cheat == 2) {

                }

            }


            ImGui::SetCursorPos(ImVec2(357, 230));
            if (Controls::IconButton(skCrypt("HELP"), Images::imageStatus, ImVec2(85, 30))) {

                user_profile = true;
            }



            // Convert the string to a std::tm structure
            std::tm expirationDate = {};
            std::istringstream dateStream(auth::get_subexpiry().c_str());
            dateStream >> std::get_time(&expirationDate, "%Y-%m-%d");

            // Call the function to get the formatted countdown
            std::string countdownString = getSubscriptionCountdown(expirationDate);
            ImGui::SetCursorPos(ImVec2(14, 270));
            DrawList::Text(skCrypt("txt9"), skCrypt("Subscription expires in -> "), ImGui::GetFont(), 14, ImVec2(14, 268), ImColor(54, 56, 71));
            DrawList::Text(skCrypt("txt9"), countdownString.c_str(), ImGui::GetFont(), 14, ImVec2(155, 268), ImColor(0, 255, 0));

        }
    
    }
}
