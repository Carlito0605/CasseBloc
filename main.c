#include <stdio.h>
#include <stdlib.h>
#include "bombs.h"

int main() {
    //printf("Hello, World!\n"); //affiche

    Player player_1 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .bombs = malloc(sizeof (Bomb)*2)
    };

    Player player_2 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .bombs = malloc(sizeof (Bomb)*2)
    };

    Player player_3 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .bombs = malloc(sizeof (Bomb)*2)
    };

    Player player_4 = {
            .hp = 3,
            .max_hp = 3,
            .max_bombs = 2,
            .bombs = malloc(sizeof (Bomb)*2)
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    test(10,15, players);

    return 0;
}
