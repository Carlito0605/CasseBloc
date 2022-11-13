#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bombs.h"

int main() {

    //printf("Hello, World!\n"); //affiche

    srand(time(NULL));

    Player player_1 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .bomb_special_power_up = -1,
            .heart=0
    };

    Player player_2 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .bomb_special_power_up = -1,
            .heart=0
    };

    Player player_3 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .bomb_special_power_up = -1,
            .heart=0
    };

    Player player_4 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .range = 2,
            .current_bombs = 2,
            .bomb_special_power_up = -1,
            .heart=0
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    test(10,15, players);

    return 0;
}
