#ifndef ENEMY_H
#define ENEMY_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>

class Player;

class Enemy {
    public:
        Enemy(int starting_x, int starting_y, bn::fixed enemy_speed, bn::size enemy_size);

        void update(const Player& player);

        void respawn();

        bn::sprite_ptr sprite;
        bn::fixed speed;
        bn::size size;
        bn::rect bounding_box;

    private:
        void update_bounding_box();
};

#endif