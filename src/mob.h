#ifndef MOB_H
#define MOB_H

#include <RigidBody2D.hpp>
#include <Godot.hpp>
#include <random>

namespace godot {

    class Mob : public RigidBody2D {
    GODOT_CLASS(Mob, RigidBody2D)

    public:
        static void _register_methods();

        void _init();

        void _ready();

        void _on_visibility_screen_exited();

    private:
        // Minimum speed range.
        int min_speed;
        // Maximum speed range.
        int max_speed;
        Array mob_types = Array::make<String>("walk", "swim", "fly");
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution;
    };
}   // namespace godot

#endif // MOB_H
