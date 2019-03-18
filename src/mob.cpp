#include <gen/AnimatedSprite.hpp>
#include "mob.h"

using namespace godot;

void Mob::_register_methods() {
    register_method("_ready", &Mob::_ready);
    register_method("_on_visibility_screen_exited", &Mob::_on_visibility_screen_exited);
    register_property<Mob, int>("min_speed", &Mob::min_speed, 150);
    register_property<Mob, int>("max_speed", &Mob::max_speed, 250);
}

void Mob::_init() {
    min_speed = 150;
    max_speed = 250;
    distribution = std::uniform_int_distribution<int>(0, mob_types.size());
}

void Mob::_ready() {
    get_node("Visibility")->connect("screen_exited", this, "_on_visibility_screen_exited");
    cast_to<AnimatedSprite>(get_node("AnimatedSprite"))->set_animation(mob_types[distribution(generator)]);
}

void Mob::_on_visibility_screen_exited() {
    queue_free();
}
