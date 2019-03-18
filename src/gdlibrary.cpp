#include <Godot.hpp>
#include "player.h"
#include "mob.h"
#include "main.h"
#include "hud.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options* options) {
    godot::Godot::gdnative_init(options);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options* options) {
    godot::Godot::gdnative_terminate(options);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
    godot::Godot::nativescript_init(handle);
    godot::register_class<godot::Player>();
    godot::register_class<godot::Mob>();
    godot::register_class<godot::Main>();
    godot::register_class<godot::Hud>();
}
