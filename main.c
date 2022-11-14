#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bombs.h"
#include "time.h"

int main() {

    //printf("Hello, World!\n"); //affiche

    srand(time(NULL));

    ///Players Inits :

    Player player_1 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="ABC",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_2 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="DEF",
            .dead = 0,
            .v_pos = 3,
            .h_pos = 7
    };

    Player player_3 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="GHI",
            .dead = 0,
            .v_pos = 5,
            .h_pos = 5
    };

    Player player_4 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="JKL",
            .dead = 0,
            .v_pos = 2,
            .h_pos = 2
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    test(10,15, players); //Function to test that bombs are working

    return 0;
}
