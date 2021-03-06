#include "player.h"
#include <Input.hpp>
#include <Viewport.hpp>
#include <AnimatedSprite.hpp>
#include <gen/CollisionShape2D.hpp>
#include <gen/InputEventScreenTouch.hpp>

using namespace godot;

void Player::_register_methods() {
    register_method("_input", &Player::_input);
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("_on_player_body_entered", &Player::_on_player_body_entered);
    register_property<Player, int>("speed", &Player::speed, 400);
    register_signal<Player>("hit");
}

void Player::_init() {
    speed = 400;
}

void Player::_ready() {
    connect("body_entered", this, "_on_player_body_entered");

    screen_size = get_viewport()->get_size();
    hide();
}

void Player::_input(const godot::Ref<godot::InputEvent> event) {
    // Change the target whenever a touch happens.
    auto* screen_touch_event = cast_to<InputEventScreenTouch>(*event);
    if (screen_touch_event && screen_touch_event->is_pressed()) {
        click_target = screen_touch_event->get_position();
    }
}

void Player::_process(float delta) {
    Vector2 velocity; // The player's movement vector.
    // Move toward the target and stop when close.
    Vector2 position = get_position();
    if (position.distance_to(click_target) > 10) {
        velocity = (click_target - position).normalized() * speed;
    } else {
        velocity = Vector2();
    }

    auto *animated_sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
    if (velocity.length() > 0) {
        velocity = velocity.normalized() * speed;
        animated_sprite->play();
    } else {
        animated_sprite->stop();
    }

    Vector2 new_pos = position + (velocity * delta);
    set_position(new_pos);

    if (velocity.x != 0) {
        animated_sprite->set_animation("right");
        animated_sprite->set_flip_h(velocity.x < 0);
        animated_sprite->set_flip_v(false);
    } else if (velocity.y != 0) {
        animated_sprite->set_animation("up");
        animated_sprite->set_flip_v(velocity.y > 0);
    }
}

void Player::_on_player_body_entered(godot::PhysicsBody2D *body) {
    hide(); // Player disappears after being hit.
    emit_signal("hit");
    cast_to<CollisionShape2D>(get_node("CollisionShape2D"))->set_disabled(true);
}

void Player::start(godot::Vector2 pos) {
    set_position(pos);
    // Initial target is the start position.
    click_target = pos;
    show();
    cast_to<CollisionShape2D>(get_node("CollisionShape2D"))->set_disabled(false);
}
