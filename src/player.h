#ifndef PLAYER_H
#define PLAYER_H

#include <Area2D.hpp>
#include <Godot.hpp>
#include <InputEvent.hpp>
#include <PhysicsBody2D.hpp>

namespace godot {

    class Player : public Area2D {
    GODOT_CLASS(Player, Area2D)

    public:
        static void _register_methods();

        void _init();
        void _ready();
        void _process(float delta);
        void _input(const Ref<InputEvent> event);
        void _on_player_body_entered(PhysicsBody2D* body);
        void start(Vector2 pos);

    private:
        // How fast the player will move (pixels / sec).
        int speed;
        // Size of the game window.
        Vector2 screen_size;
        // Hold the clicked position.
        Vector2 click_target;
    };

}   // namespace godot

#endif // PLAYER_H
