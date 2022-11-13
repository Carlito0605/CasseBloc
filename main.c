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
            .bombs_car="ABC"
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
            .bombs_car="DEF"
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
            .bombs_car="GHI"
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
            .bombs_car="JKL"
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    test(10,15, players); //Function to test that bombs are working

    return 0;
}
