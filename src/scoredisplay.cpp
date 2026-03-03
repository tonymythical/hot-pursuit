#include "scoredisplay.h"
#include "common_fixed_8x16_font.h"

ScoreDisplay::ScoreDisplay() :
    score(0),
    high_score(0),
    text_generator(common::fixed_8x16_sprite_font)
{
}

void ScoreDisplay::update() {
    score++;
    if(score > high_score) {
        high_score = score;
    }

    // Clear old sprites before drawing new ones
    score_sprites.clear();

    // Draw Score (Right side) and High Score (Left side)
    show_number(70, -70, score);
    show_number(-70, -70, high_score);
}

void ScoreDisplay::show_number(int x, int y, int number) {
    bn::string<MAX_CHARS> number_string = bn::to_string<MAX_CHARS>(number);
    text_generator.generate(x, y, number_string, score_sprites);
}

void ScoreDisplay::resetScore() {
    score = 0;
}