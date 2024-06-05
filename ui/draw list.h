#pragma once

namespace DrawList
{
    void Line(const char* label, ImVec2 size, ImVec2 location, ImColor col, float thickness) {
        auto drawList = ImGui::GetWindowDrawList();
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 topLeft = ImVec2(location.x + windowPos.x, location.y + windowPos.y);
        ImVec2 bottomRight = ImVec2(topLeft.x + size.x, topLeft.y + size.y);

        ImVec2 topLeftInner = ImVec2(topLeft.x + thickness, topLeft.y + thickness);
        ImVec2 bottomRightInner = ImVec2(bottomRight.x - thickness, bottomRight.y - thickness);
        drawList->AddLine(topLeftInner, ImVec2(bottomRightInner.x, topLeftInner.y), col, thickness);
    }

    void Text(const char* label, const char* text, const ImFont* font, float font_size, ImVec2 location, ImColor col) {
        auto drawList = ImGui::GetWindowDrawList();
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 textPos = ImVec2(location.x + windowPos.x, location.y + windowPos.y);
        drawList->AddText(font, font_size, textPos, col, text);
    }

    void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }
}