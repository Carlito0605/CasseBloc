#include "main.h"

void displayMap(char**map, int rows, int columns){
    for(int i = -1; i<columns; i++){
        if(i!=-1) printf("%2d ",i);
        else printf("   ");
    }
    printf("\n");
    for(int i = -1; i<columns; i++){
        if(i!=-1) printf("__ ");
        else printf("   ");
    }
    printf("\n");
    for(int i = 0; i<rows; i++){
        printf("%d | ",i);
        for(int y = 0; y<columns; y++){
            printf("%c  ",map[i][y]);
        }
        printf("|\n");
    }
    for(int i = -1; i<columns; i++){
        if(i!=-1) printf("__ ");
        else printf("   ");
    }
    printf("\n");
}

char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range){

    map[v_pos][h_pos] = 'X';

    for(int i = 1; i<=range; i++){
        if((v_pos+i) < rows){
            if(map[v_pos+i][h_pos] != '*' && map[v_pos+i][h_pos] != 'X' && map[v_pos+i][h_pos] != '.'){
                map = bombExplosion(map,rows,columns,v_pos+i,h_pos,2);
                map[v_pos+i][h_pos] = 'X';
            }
            else if(map[v_pos+i][h_pos] != 'X' && map[v_pos+i][h_pos] != '*'){
                map[v_pos+i][h_pos] = '*';
            }
        }
        if((v_pos-i) >= 0){
            if(map[v_pos-i][h_pos] != '*' && map[v_pos-i][h_pos] != 'X' && map[v_pos-i][h_pos] != '.'){
                map = bombExplosion(map,rows,columns,v_pos-i,h_pos,2);
                map[v_pos-i][h_pos] = 'X';
            }
            else if(map[v_pos-i][h_pos] != 'X' && map[v_pos-i][h_pos] != '*'){
                map[v_pos-i][h_pos] = '*';
            }
        }
        if((h_pos+i) < columns){
            if(map[v_pos][h_pos+i] != '*' && map[v_pos][h_pos+i] != 'X' && map[v_pos][h_pos+i] != '.'){
                map = bombExplosion(map,rows,columns,v_pos,h_pos+i,2);
                map[v_pos][h_pos+i] = 'X';
            }
            else if(map[v_pos][h_pos+i] != 'X' && map[v_pos][h_pos+i] != '*'){
                map[v_pos][h_pos+i] = '*';
            }
        }
        if((h_pos-i) >= 0){
            if(map[v_pos][h_pos-i] != '*' && map[v_pos][h_pos-i] != 'X' && map[v_pos][h_pos-i] != '.'){
                map = bombExplosion(map,rows,columns,v_pos,h_pos-i,2);
                map[v_pos][h_pos-i] = 'X';
            }
            else if(map[v_pos][h_pos-i] != 'X' && map[v_pos][h_pos-i] != '*'){
                map[v_pos][h_pos-i] = '*';
            }
        }
    }

    return map;
}

char** checkBombs(char**map, int rows, int columns, Player* players, char* bomb_car){

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            if(map[i][y] == bomb_car[0]){
                map[i][y] = bomb_car[1];
            }
            else if(map[i][y] == bomb_car[1]){
                map[i][y] = bomb_car[2];
            }
            else if(map[i][y] == bomb_car[2]){
                //map[i][y] = 'X';
                int range = 2;
                switch (bomb_car[2]) {
                    case 'C':
                        range = players[0].range;
                        players[0].current_bombs++;
                        if(players[0].current_bombs > players[0].max_bombs) players[0].current_bombs = players[0].max_bombs;
                        break;
                    case 'F':
                        range = players[1].range;
                        players[1].current_bombs++;
                        if(players[1].current_bombs > players[1].max_bombs) players[1].current_bombs = players[1].max_bombs;
                        break;
                    case 'I':
                        range = players[2].range;
                        players[2].current_bombs++;
                        if(players[2].current_bombs > players[2].max_bombs) players[2].current_bombs = players[2].max_bombs;
                        break;
                    case 'L':
                        range = players[3].range;
                        players[3].current_bombs++;
                        if(players[3].current_bombs > players[3].max_bombs) players[3].current_bombs = players[3].max_bombs;
                        break;
                }
                map = bombExplosion(map,rows,columns,i,y,range);
            }
        }
    }

    return map;
}

char** dropBomb(char**map, int v_pos, int h_pos, Player* player, char* bomb_car){

    if(map[v_pos][h_pos] == '.'){
        if(player->current_bombs > 0){
            map[v_pos][h_pos] = bomb_car[0];
            player->current_bombs--;
            printf("Vous avez pose une bombe %c, il vous en reste %d\n",bomb_car[0],player->current_bombs);
        }
        else printf("Vous n'avez plus assez de bombes !\n");
    }
    else printf("Vous ne pouvez pas placer de bombe ici car : %c \n",map[v_pos][h_pos]);

    return map;
}

void test(int rows, int columns, Player* players){

    char** map = malloc(sizeof (char*)*rows);
    for(int i = 0; i<rows; i++){
        map[i] = malloc(sizeof (char)*columns);
        for(int y = 0; y<columns; y++) map[i][y] = '.';
    }

    //tests :


    //map[3][4] = 'A';
    //map[3][6] = 'D';
    //map[8][9] = 'G';
    //map[1][1] = 'J';


    //map[1][7] = 'B';
    //map[9][4] = 'E';
    //map[3][4] = 'H';
    //map[9][1] = 'K';


    //map[9][11] = 'C';
    //map[2][6] = 'F';
    //map[0][12] = 'I';
    //map[9][2] = 'L';


    displayMap(map,rows,columns);

    char* player_1_bomb_car = "ABC";
    char* player_2_bomb_car = "DEF";
    char* player_3_bomb_car = "GHI";
    char* player_4_bomb_car = "JKL";

    map = checkBombs(map,rows,columns,players,player_1_bomb_car);
    map = checkBombs(map,rows,columns,players,player_2_bomb_car);
    map = checkBombs(map,rows,columns,players,player_3_bomb_car);
    map = checkBombs(map,rows,columns,players,player_4_bomb_car);

    printf("\nNew map :\n");

    displayMap(map,rows,columns);

    map = dropBomb(map,5,7,&players[0],player_1_bomb_car);
    /*
    map = dropBomb(map,5,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,4,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,3,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,2,7,&players[0],player_1_bomb_car);
    */
    printf("\nNew map :\n");

    displayMap(map,rows,columns);

    free(map);
}