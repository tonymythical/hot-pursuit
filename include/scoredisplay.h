#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include <bn_vector.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_string.h>

class ScoreDisplay {
    public:
        ScoreDisplay();

        void update();

        void resetScore();

        void show_number(int x, int y, int number);

    private:
        static constexpr int MAX_CHARS = 22;
        int score;
        int high_score;
        
        bn::vector<bn::sprite_ptr, MAX_CHARS> score_sprites;
        bn::sprite_text_generator text_generator;
};

#endif