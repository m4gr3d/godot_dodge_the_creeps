#include <Timer.hpp>
#include <Position2D.hpp>
#include <PathFollow2D.hpp>
#include <gen/ResourceLoader.hpp>
#include "main.h"
#include "player.h"
#include "mob.h"
#include "hud.h"

using namespace godot;

void Main::_register_methods() {
    register_method("_ready", &Main::_ready);
    register_method("game_over", &Main::game_over);
    register_method("new_game", &Main::new_game);
    register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
    register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
    register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
    register_property<Main, Ref<PackedScene>>("mob", &Main::mob,
                                              ResourceLoader::get_singleton()->load("res://Mob.tscn"));
}

void Main::_init() {
    score = 0;
    mob = ResourceLoader::get_singleton()->load("res://Mob.tscn");
}

void Main::_ready() {
    get_node("Player")->connect("hit", this, "game_over");
    get_node("ScoreTimer")->connect("timeout", this, "_on_ScoreTimer_timeout");
    get_node("StartTimer")->connect("timeout", this, "_on_StartTimer_timeout");
    get_node("MobTimer")->connect("timeout", this, "_on_MobTimer_timeout");
    get_node("HUD")->connect("start_game", this, "new_game");
}

void Main::game_over() {
    cast_to<Timer>(get_node("MobTimer"))->stop();
    cast_to<Timer>(get_node("ScoreTimer"))->stop();

    ((Hud *) get_node("HUD"))->show_game_over();
}

void Main::new_game() {
    score = 0;

    auto *player = cast_to<Player>(get_node("Player"));
    auto *start_position = cast_to<Position2D>(get_node("StartPosition"));
    player->start(start_position->get_position());

    cast_to<Timer>(get_node("StartTimer"))->start();

    auto *hud = ((Hud *) get_node("HUD"));
    hud->update_score(score);
    hud->show_message("Get Ready!");
}

void Main::_on_MobTimer_timeout() {
    // Choose a random location on Path2D.
    auto *mob_spawn_location = cast_to<PathFollow2D>(get_node("MobPath/MobSpawnLocation"));
    mob_spawn_location->set_offset(rand());

    // Create a Mob instance and add it to the scene.
    auto *mob_instance = cast_to<RigidBody2D>(mob->instance());
    add_child(mob_instance);

    // Set the mob's direction perpendicular to the path direction.
    float direction = mob_spawn_location->get_rotation() + Math_PI / 2;

    // Set the mob's position to a random location.
    mob_instance->set_position(mob_spawn_location->get_position());

    // Add some randomness to the direction.
    direction += rand_range(-Math_PI / 4, Math_PI / 4);
    mob_instance->set_rotation(direction);

    // Choose the velocity
    mob_instance->set_linear_velocity(Vector2(rand_range(150.0f, 250.0f), 0).rotated(direction));
}

void Main::_on_StartTimer_timeout() {
    cast_to<Timer>(get_node("MobTimer"))->start();
    cast_to<Timer>(get_node("ScoreTimer"))->start();
}

void Main::_on_ScoreTimer_timeout() {
    score++;
    ((Hud *) get_node("HUD"))->update_score(score);
}

float Main::rand_range(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max + 1);
    return distribution(generator);
}
