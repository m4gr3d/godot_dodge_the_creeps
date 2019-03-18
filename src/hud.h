#ifndef HUD_H
#define HUD_H

#include <gen/CanvasLayer.hpp>
#include <core/Godot.hpp>

namespace godot {

    class Hud : public CanvasLayer {
        GODOT_CLASS(Hud, CanvasLayer)

    public:
        static void _register_methods();

        void _init();
        void _ready();
        void show_message(String text);
        void show_game_over();
        void update_score(int score);
        void on_StartButton_pressed();
        void on_MessageTimer_timeout();

    private:
        bool is_game_over = false;
    };

}   // namespace godot

#endif // HUD_H
