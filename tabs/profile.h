#pragma once

namespace tabs {
	void user_tab() {
		RECT screen_rect;
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		auto x = float(screen_rect.right - 250) / 2.f;
		auto y = float(screen_rect.bottom - 155) / 2.f;

		ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 155));

		ImGui::Begin(skCrypt("##profile"), &user_profile, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		{
			auto draw = ImGui::GetWindowDrawList();
			ImVec2 pos = ImGui::GetWindowPos();
			ImVec2 size = ImGui::GetWindowSize();

			draw->AddRectFilled(ImGui::GetWindowPos(), ImVec2(pos.x + size.x, pos.y + 35), ImColor(3, 7, 19));
			draw->AddText(font, 16, ImVec2(pos.x + 10, pos.y + 10), ImColor(255, 255, 255), skCrypt("INSTRUCTIONS"));

			ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 30, 8));
			if (Controls::ExitButton(skCrypt("##exit2"), Images::imageExit, ImVec2(20, 20))) user_profile = false;

			DrawList::Text(skCrypt("usertxt1"), skCrypt("[1] Make sure all antivirus / anticheat software is closed").decrypt(), ImGui::GetFont(), 14, ImVec2(15, 45), ImColor(255, 255, 255));
			DrawList::Text(skCrypt("usertxt2"), skCrypt("[2] Make sure you are spoofed (use inbuilt spoofer)").decrypt(), ImGui::GetFont(), 14, ImVec2(15, 65), ImColor(255, 255, 255));
			DrawList::Text(skCrypt("usertxt3"), skCrypt("[3] Select the purchased product and click LAUNCH").decrypt(), ImGui::GetFont(), 14, ImVec2(15, 85), ImColor(255, 255, 255));
			DrawList::Text(skCrypt("usertxt4"), skCrypt("[4] Follow the instructions on the created window").decrypt(), ImGui::GetFont(), 14, ImVec2(15, 105), ImColor(255, 255, 255));
			DrawList::Text(skCrypt("usertxt5"), skCrypt("[5] Press F9 once you are in lobby").decrypt(), ImGui::GetFont(), 14, ImVec2(15, 125), ImColor(255, 255, 255));
		}
		ImGui::End();
	}
}