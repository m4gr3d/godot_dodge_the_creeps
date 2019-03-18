#include <gen/Label.hpp>
#include <gen/Timer.hpp>
#include <gen/Button.hpp>
#include "hud.h"

using namespace godot;

void Hud::_register_methods() {
    register_method("_ready", &Hud::_ready);
    register_method("show_message", &Hud::show_message);
    register_method("show_game_over", &Hud::show_game_over);
    register_method("update_score", &Hud::update_score);
    register_method("on_StartButton_pressed", &Hud::on_StartButton_pressed);
    register_method("on_MessageTimer_timeout", &Hud::on_MessageTimer_timeout);
    register_signal<Hud>("start_game");
}

void Hud::_init() {
    is_game_over = false;
}

void Hud::_ready() {
    get_node("MessageTimer")->connect("timeout", this, "on_MessageTimer_timeout");
    get_node("StartButton")->connect("pressed", this, "on_StartButton_pressed");
}

void Hud::show_message(godot::String text) {
    auto* message_label = cast_to<Label>(get_node("MessageLabel"));
    message_label->set_text(text);
    message_label->show();

    cast_to<Timer>(get_node("MessageTimer"))->start();
}

void Hud::show_game_over() {
    is_game_over = true;
    show_message("Game Over");
}

void Hud::update_score(int score) {
    auto* score_label = ((Label*) get_node("ScoreLabel"));
    score_label->set_text(String::num(score));
}

void Hud::on_StartButton_pressed() {
    ((Button*) get_node("StartButton"))->hide();
    ((Label*) get_node("MessageLabel"))->hide();
    emit_signal("start_game");
}

void Hud::on_MessageTimer_timeout() {
    auto* message_label = (Label*) get_node("MessageLabel");
    if (is_game_over) {
        is_game_over = false;

        message_label->set_text("Dodge the Creeps!");
        message_label->show();

        ((Button *) get_node("StartButton"))->show();
    } else {
        message_label->hide();
    }
}