#ifndef MAIN_H
#define MAIN_H

#include <random>
#include <Node.hpp>
#include <Godot.hpp>
#include <PackedScene.hpp>

namespace godot {

    class Main : public Node {
        GODOT_CLASS(Main, Node)

    public:
        static void _register_methods();

        void _init();
        void _ready();
        void game_over();
        void new_game();
        void _on_MobTimer_timeout();
        void _on_ScoreTimer_timeout();
        void _on_StartTimer_timeout();

    private:
        float rand_range(float min, float max);

        Ref<PackedScene> mob;
        int score;
        std::default_random_engine generator;
    };

}   // namespace godot

#endif // MAIN_H
