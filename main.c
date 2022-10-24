#include <stdio.h>
#include <string.h>

typedef struct {
    int range;
    int current_timer;
}Bomb;

typedef struct
{
    int hp;
    int max_hp;
    Bomb* bombs;
    int max_bombs;
} Player;

int main() {
    for(int x = 0; x< xmap;x++){
        for(int y = 0; y< ymap; y++){
            if(haut == 1 && joeur[positionx][positiony + 1] == ' '){
                joeur[positionx][positiony + 1];
            };
            elseif(gauche == 1 && joeur[positionx - 1][positiony]== ' '){
                joeur[positionx - 1][positiony];
            };

            elseif(droite == 1 && joeur[positionx + 1][positiony]== ' '){
                joeur[positionx + 1][positiony];
            };
            elseif(bas == 1 && joeur[positionx][positiony - 1]== ' '){
                joeur[positionx][positiony - 1];
            };
            if(dropBomb()){
                map[x][y]='X';
            }
        };
    };
}





