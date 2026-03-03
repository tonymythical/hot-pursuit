#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_random.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"

#include "scoredisplay.h"
#include "player.h"
#include "enemy.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 22;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

// Random generator
bn::random random;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

/**
 * Displays a score and high score.
 * 
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
*/

int main() {
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay;

    // Create a player and initialize it
    Player player(-50, 22, 3.5, PLAYER_SIZE);

    static constexpr int MAX_ENEMIES = 8;
    bn::vector<Enemy, MAX_ENEMIES> enemies;

    enemies.push_back(Enemy(60, 40, 0.4, ENEMY_SIZE));
    // enemies.push_back(Enemy(-60, -40, 0.6, ENEMY_SIZE));
    // enemies.push_back(Enemy(0, -60, 0.3, ENEMY_SIZE));

    // frame counter to track
    int frame_counter = 0;
    const int SPAWN_RATE = 300;

    while(true) {
        player.update();
        frame_counter++;

        if(frame_counter >= SPAWN_RATE && !enemies.full()) {
            int rx = random.get_int(MIN_X + 10, MAX_X - 10);
            int ry = random.get_int(MIN_Y + 10, MAX_Y - 10);
            
            enemies.push_back(Enemy(rx, ry, 0.5, ENEMY_SIZE));
            frame_counter = 0; 
        }

        bool player_hit = false;

        for(Enemy& enemy : enemies) {
            enemy.update(player);

            if(enemy.bounding_box.intersects(player.bounding_box)) {
                player_hit = true;
                break; 
            }
        }

        // Reset.
        if(player_hit) {
            scoreDisplay.resetScore();
            player.sprite.set_position(-50, 22);

            while(enemies.size() > 1) {
                enemies.pop_back();
            }

            // Move the remaining enemy to a random spot to prevent collision
            enemies[0].respawn();
            frame_counter = 0;
        }
        
        // Reset the current score and player position if the player collides with enemy
        for(Enemy& enemy : enemies) {
            enemy.update(player);
            if(enemy.bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(-50);
                player.sprite.set_y(22);

                for(Enemy& e : enemies) {
                    e.respawn();
                }

                break; // Stop the check
            }

        }

        

        // Update the scores and disaply them
        scoreDisplay.update();
        

        bn::core::update();
    }
}