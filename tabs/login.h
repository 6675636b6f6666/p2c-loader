#pragma comment(lib, "Login.lib")

void RemoteLogin();

namespace auth {

    std::string get_subexpiry();
    std::string get_username();
    std::string get_status();

}

void MessageBoxUi(const char* title, const char* message) {
    vars::show_message_box = true;
    vars::message_box_title = title;
    vars::message_box_message = message;
}




std::string username;
std::string token;

std::string get_str_between_two_str(const std::string& s,
    const std::string& start_delim,
    const std::string& stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim,
        last_delim_pos - end_pos_of_first_delim);
}




namespace tabs {
    void login_tab() {
        //       window_width = 265; window_height = 320;

        //       ImGui::SetCursorPos(ImVec2(25, 55));
        //       if (Controls::IconButton(skCrypt("DISCORD"), Images::imageDiscord, ImVec2(88, 30))) {
        //           ShellExecute(NULL, skCrypt("open"), skCrypt("https://discord.gg/GbAvmCnE2V"), NULL, NULL, SW_SHOWNORMAL);
        //       }

        //       ImGui::SetCursorPos(ImVec2(145, 55));
        //       if (Controls::IconButton(skCrypt("YOUTUBE"), Images::imageYoutube, ImVec2(92, 30))) {
        //           ShellExecute(NULL, skCrypt("open"), skCrypt("https://www.youtube.com"), NULL, NULL, SW_SHOWNORMAL);
        //       }

        //       DrawList::Line(skCrypt("sep"), ImVec2(90, 5), ImVec2(25, 110), ImColor(23, 25, 37), 1);
        //       DrawList::Line("sep2", ImVec2(90, 5), ImVec2(150, 110), ImColor(23, 25, 37), 1);

        //       ImGui::PushStyleColor(ImGuiCol_Text, ColorFromBytes(54, 56, 71));

        //       ImGui::SetCursorPos(ImVec2(25, 140));
        //       ImGui::SetNextItemWidth(215);
        //       ImGui::InputText(skCrypt("##license"), vars::license, sizeof(vars::license), vars::show_password ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_Password);

        //       ImGui::PopStyleColor();

        //       ImGui::PushStyleColor(ImGuiCol_Text, ColorFromBytes(54, 56, 71));
        //       ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

        //       ImGui::SetCursorPos(ImVec2(25, 240));
        //       ImGui::Checkbox(skCrypt("  SHOW LICENSE"), &vars::show_password);

        //       ImGui::PopStyleColor(); ImGui::PopStyleVar(1);

        //       ImGui::SetCursorPos(ImVec2(82.5, 190));
        //       if (Controls::Button(skCrypt("LOGIN"), ImVec2(100, 30))) {


        //           std::string key(vars::license);

        //           auto resp = BitSync::license_ctx(key.c_str());

        //           BitSync::values ctx = BitSync::UNKNOWN;
        //           std::unordered_map<std::string, BitSync::values> Login = {
        //               {BitSync::get_response_invalid(), BitSync::INVALID},
        //               {BitSync::get_response_expired(), BitSync::EXPIRED},
        //               {BitSync::get_response_hwid(), BitSync::HWID},
        //               {BitSync::get_response_success(), BitSync::SUCCESS}
        //           };

        //           auto msg = Login.find(resp);
        //           if (msg != Login.end())
        //           {
        //               ctx = msg->second;
        //           }

        //           switch (ctx) { //error and login handling

        //           case BitSync::INVALID:
        //               MessageBoxA(0, "wqs", "wqd", 0);
        //               MessageBoxUi(skCrypt(" AUTHENTICATION").decrypt(), skCrypt("License not found").decrypt());
        //               break;
        //           case BitSync::EXPIRED:
        //               MessageBoxUi(skCrypt(" AUTH").decrypt(), skCrypt("Subscription expired").decrypt());
        //               break;
        //           case BitSync::HWID:
        //               MessageBoxUi(skCrypt(" AUTH").decrypt(), skCrypt("HWID missmatch").decrypt());
        //               break;
        //           case BitSync::SUCCESS:
        //               userD.saveToFile(skCrypt("C:\\ProgramData\\license.bin").decrypt());
        //               vars::selected_tab = 2;
        //               break;
        //           default:
        //               break;
        //           }

        //           
        //       }

        //       DrawList::Text(skCrypt("txt2"), skCrypt("DON'T HAVE A LICENSE YET?"), ImGui::GetFont(), 12, ImVec2(25, 295), ImColor(54, 56, 71));

        //       ImGui::SetCursorPos(ImVec2(213, 295));
        //       if (Controls::LinkLabel(skCrypt("Check our store"), ImVec2(ImVec2(20, 15)))) {
        //           ShellExecute(NULL, skCrypt("open"), skCrypt("https://beamed.tech/#shop"), NULL, NULL, SW_SHOWNORMAL);
        //       }
           //}

        

        

    }

}