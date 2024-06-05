#pragma once
#include "imfade.h"

namespace Controls 
{
	bool CheatButton(const char* label, const char* sub, IDirect3DTexture9* icon, IDirect3DTexture9* lock, const bool selected, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		auto& cheatbutton_animation = imfade::Animation<std::string>::get(label);
		cheatbutton_animation.init();

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		if (selected)
		{
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBgHovered, cheatbutton_animation.fade_anim), 3.f);
			window->DrawList->AddImage((void*)(intptr_t)icon, ImVec2(bb.Min.x + 10, bb.Min.y + 8), ImVec2(bb.Min.x + 10 + 32, bb.Min.y + 40), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, cheatbutton_animation.fade_anim));
			window->DrawList->AddText({ bb.Min.x + 52, bb.Min.y + 5 }, ImGui::GetColorU32(ImGuiCol_Text, cheatbutton_animation.fade_anim), label);
			window->DrawList->AddText({ bb.Min.x + 52, bb.Min.y + 28 }, ImGui::GetColorU32(ImGuiCol_TextDisabled, cheatbutton_animation.fade_anim), skCrypt("UPDATED"));
			window->DrawList->AddText({ bb.Min.x + 83, bb.Min.y + 28 }, ImGui::GetColorU32(ImGuiCol_Border, cheatbutton_animation.fade_anim), sub);
			window->DrawList->AddImage((void*)(intptr_t)lock, ImVec2(bb.Max.x - 21.0f - style.FramePadding.x, bb.Min.y + (size.y - 16.0f) / 2.0f), ImVec2(bb.Max.x - style.FramePadding.x - 5.0f, bb.Min.y + (size.y - 16.0f) / 2.0f + 16.0f), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, cheatbutton_animation.fade_anim));
		}
		else
		{
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg, cheatbutton_animation.fade_anim), 3.f);
			window->DrawList->AddImage((void*)(intptr_t)icon, ImVec2(bb.Min.x + 10, bb.Min.y + 8), ImVec2(bb.Min.x + 10 + 32, bb.Min.y + 40), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, cheatbutton_animation.fade_anim));
			window->DrawList->AddText({ bb.Min.x + 52, bb.Min.y + 5 }, ImGui::GetColorU32(ImGuiCol_Text, cheatbutton_animation.fade_anim), label);
			window->DrawList->AddText({ bb.Min.x + 52, bb.Min.y + 28 }, ImGui::GetColorU32(ImGuiCol_TextDisabled, cheatbutton_animation.fade_anim), skCrypt("UPDATED"));
			window->DrawList->AddText({ bb.Min.x + 83, bb.Min.y + 28 }, ImGui::GetColorU32(ImGuiCol_Border, cheatbutton_animation.fade_anim), sub);
		}

		if (pressed) {
			cheatbutton_animation.restart_fade_in();
		}

		return pressed;
	}

	bool Button(const char* label, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		auto& button_animation = imfade::Animation<std::string>::get(label);
		button_animation.init();

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		ImVec2 text_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 text_pos = { bb.Min.x + (size.x - text_size.x) / 2, bb.Min.y + (size.y - text_size.y) / 2 };

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_Button, button_animation.fade_anim), 3.f);

		if (hovered)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonHovered, button_animation.fade_anim), 3.f);

		if (held)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonActive, button_animation.fade_anim), 3.f);

		window->DrawList->AddText(g.Font, g.FontSize, text_pos, ImGui::GetColorU32(ImGuiCol_Text, button_animation.fade_anim), label);

		if (pressed) {
			button_animation.restart_fade_in();
		}

		return pressed;
	}

	bool ExitButton(const char* label, IDirect3DTexture9* icon, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonActive), 3.f);

		if (hovered)
		{
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonHovered), 3.f);
		}

		if (held)
		{
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_Border), 3.f);
		}

		ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)icon, ImVec2(bb.Min.x + (size.x - 14) / 2, bb.Min.y + size_arg.y / 2 - 6), ImVec2(bb.Min.x + (size.x - 14) / 2 + 14, bb.Min.y + size_arg.y / 2 + 6), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text));

		return pressed;
	}

	bool IconButton(const char* label, IDirect3DTexture9* icon, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImVec2 icon_size(16.0f, 16.0f);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + icon_size.x + style.FramePadding.x * 3.0f, ImMax(label_size.y, icon_size.y) + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		auto& iconbutton_animation = imfade::Animation<std::string>::get(label);
		iconbutton_animation.init();

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		ImVec2 text_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 icon_pos = { bb.Min.x + style.FramePadding.x, bb.Min.y + (size.y - icon_size.y) / 2 };
		ImVec2 text_pos = { icon_pos.x + icon_size.x + style.FramePadding.x, bb.Min.y + (size.y - text_size.y) / 2 };

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_Button, iconbutton_animation.fade_anim), style.FrameRounding);

		if (hovered)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonHovered, iconbutton_animation.fade_anim), style.FrameRounding);

		if (held)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonActive, iconbutton_animation.fade_anim), style.FrameRounding);

		window->DrawList->AddImage(icon, icon_pos, ImVec2(icon_pos.x + icon_size.x, icon_pos.y + icon_size.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, iconbutton_animation.fade_anim));

		window->DrawList->AddText(g.Font, g.FontSize, text_pos, ImGui::GetColorU32(ImGuiCol_Text, iconbutton_animation.fade_anim), label);

		if (pressed) {
			iconbutton_animation.restart_fade_in();
		}

		return pressed;
	}

	bool InjectButton(const char* label, IDirect3DTexture9* icon, const ImVec2& size_arg, bool enabled)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		const ImVec2 icon_size(16.0f, 16.0f);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + icon_size.x + style.FramePadding.x * 3.0f, ImMax(label_size.y, icon_size.y) + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImVec2 text_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 icon_pos = { bb.Min.x + style.FramePadding.x, bb.Min.y + (size.y - icon_size.y) / 2 };
		ImVec2 text_pos = { icon_pos.x + icon_size.x + style.FramePadding.x, bb.Min.y + (size.y - text_size.y) / 2 };

		auto& injectbutton_animation = imfade::Animation<std::string>::get(label);
		injectbutton_animation.init();

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!enabled || !ImGui::ItemAdd(bb, id))
		{
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_Button, injectbutton_animation.fade_anim), style.FrameRounding);
			window->DrawList->AddImage(Images::imageLock, icon_pos, ImVec2(icon_pos.x + icon_size.x, icon_pos.y + icon_size.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, injectbutton_animation.fade_anim));
			window->DrawList->AddText(g.Font, g.FontSize, text_pos, ImGui::GetColorU32(ImGuiCol_Text, injectbutton_animation.fade_anim), skCrypt("LOCKED"));
			return false;
		}

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_Button, injectbutton_animation.fade_anim), style.FrameRounding);

		if (hovered)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonHovered, injectbutton_animation.fade_anim), style.FrameRounding);

		if (held)
			window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_ButtonActive, injectbutton_animation.fade_anim), style.FrameRounding);

		window->DrawList->AddImage(icon, icon_pos, ImVec2(icon_pos.x + icon_size.x, icon_pos.y + icon_size.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(ImGuiCol_Text, injectbutton_animation.fade_anim));

		window->DrawList->AddText(g.Font, g.FontSize, text_pos, ImGui::GetColorU32(ImGuiCol_Text, injectbutton_animation.fade_anim), label);

		if (pressed) {
			injectbutton_animation.restart_fade_in();
		}

		return pressed;
	}

	bool LinkLabel(const char* label, const ImVec2& size_arg)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
		const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });

		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		auto& linkbutton_animation = imfade::Animation<std::string>::get(label);
		linkbutton_animation.init();

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

		ImVec2 text_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 text_pos = { bb.Min.x + (size.x - text_size.x) / 2, bb.Min.y + (size.y - text_size.y) / 2 };

		if (held)
		{
			window->DrawList->AddText(g.Font, 12, text_pos, ImGui::GetColorU32(ImGuiCol_Border, linkbutton_animation.fade_anim), label);
		}
		else
		{
			window->DrawList->AddText(g.Font, 12, text_pos, ImGui::GetColorU32(ImGuiCol_Text, linkbutton_animation.fade_anim), label);
		}

		if (pressed) {
			linkbutton_animation.restart_fade_in();
		}

		return pressed;
	}
}