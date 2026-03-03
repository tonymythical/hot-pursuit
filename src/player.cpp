#include "player.h"
#include <bn_keypad.h>
#include <bn_display.h>

#include "bn_sprite_items_dot.h"

Player::Player(int starting_x, int starting_y, bn::fixed player_speed, bn::size player_size) : 
    sprite(bn::sprite_items::dot.create_sprite(starting_x, starting_y)), 
    speed(player_speed),
    size(player_size),
    bounding_box(starting_x, starting_y, player_size.width(), player_size.height())
{
}

void Player::update() {
    if(bn::keypad::right_held()) {
        sprite.set_x(sprite.x() + speed);
    }
    if(bn::keypad::left_held()) {
        sprite.set_x(sprite.x() - speed);
    }
    if(bn::keypad::up_held()) {
        sprite.set_y(sprite.y() - speed);
    }
    if(bn::keypad::down_held()) {
        sprite.set_y(sprite.y() + speed);
    }

    bn::fixed x_limit = (bn::display::width() / 2) - (size.width() / 2);
    bn::fixed y_limit = (bn::display::height() / 2) - (size.height() / 2);

    sprite.set_x(bn::clamp(sprite.x(), -x_limit, x_limit));
    sprite.set_y(bn::clamp(sprite.y(), -y_limit, y_limit));

    update_bounding_box();
}

void Player::update_bounding_box() {
    bounding_box.set_position(sprite.x().round_integer(), 
                               sprite.y().round_integer());
}