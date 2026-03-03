#include "enemy.h"
#include "player.h"
#include <bn_random.h>
#include <bn_display.h>

#include "bn_sprite_items_square.h"

extern bn::random random;

Enemy::Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size) : 
    sprite(bn::sprite_items::square.create_sprite(starting_x, starting_y)),
    speed(enemy_speed),
    size(enemy_size),
    bounding_box(starting_x, starting_y, enemy_size.width(), enemy_size.height())
{
}

void Enemy::update(const Player& player) {
    if(player.sprite.x() > sprite.x()) {
        sprite.set_x(sprite.x() + speed);
    } else if(player.sprite.x() < sprite.x()) {
        sprite.set_x(sprite.x() - speed);
    }

    if(player.sprite.y() > sprite.y()) {
        sprite.set_y(sprite.y() + speed);
    } else if(player.sprite.y() < sprite.y()) {
        sprite.set_y(sprite.y() - speed);
    }

    update_bounding_box();
}

void Enemy::respawn() {
    int limit_x = (bn::display::width() / 2) - 20;
    int limit_y = (bn::display::height() / 2) - 20;

    int new_x = random.get_int(-limit_x, limit_x);
    int new_y = random.get_int(-limit_y, limit_y);

    sprite.set_position(new_x, new_y);
    update_bounding_box();
}

void Enemy::update_bounding_box() {
    bounding_box.set_position(sprite.x().round_integer(), 
                               sprite.y().round_integer());
}