#ifndef PLAYER_H
#define PLAYER_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_fixed.h>

class Player {
    public:
        Player(int starting_x, int starting_y, bn::fixed player_speed, bn::size player_size);

        void update();

        bn::sprite_ptr sprite;
        bn::fixed speed;
        bn::size size;
        bn::rect bounding_box;

    private:
        void update_bounding_box();
};

#endif