#pragma once
#include <unordered_map>

namespace imfade
{
    template<typename ID>
    class Animation
    {
    private:
        float fade_duration = 1.0f;
        float current_time = 0.0f;
        float start_time = 0.0f;

        static std::unordered_map<ID, Animation<ID>> animations;

    public:
        float fade_anim = 1.0f;

        static Animation<ID>& get(ID id)
        {
            if (animations.count(id) == 0)
                animations.emplace(id, Animation<ID>());

            return animations.at(id);
        }

        void init()
        {
            current_time = ImGui::GetTime();

            if (current_time - start_time < fade_duration)
            {
                fade_anim = (current_time - start_time) / fade_duration;

                if (fade_anim > 1.0f)
                    fade_anim = 1.0f;
            }
        }

        void restart_fade_in()
        {
            start_time = ImGui::GetTime();
            fade_anim = 1.0f;
        }

        void restart_fade_out()
        {
            start_time = ImGui::GetTime();
            fade_anim = 1.0f;
        }
    };

    template<typename ID>
    std::unordered_map<ID, Animation<ID>> Animation<ID>::animations;
}
