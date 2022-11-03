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

void displayPlayersStats(Player * players,int players_size){
    printf("\nPlayers stats :\n");
    for(int i = 0; i<players_size; i++){
        printf("* Player %d *\n",i+1);
        printf("hp : %d\n",players[i].hp);
        printf("range : %d\n",players[i].range);
        printf("current_bombs : %d\n\n",players[i].current_bombs);
    }
}

void dropObject(){
    printf("\n#dropObject()\n");
}

void takeDamage(char player_number,Player * players){
    printf("\n#takeDamage()\n");
    switch(player_number){
        case '1':
            players[0].hp--;
            break;
        case '2':
            players[1].hp--;
            break;
        case '3':
            players[2].hp--;
            break;
        case '4':
            players[3].hp--;
            break;
    }
}

char** explosionAtThatPlace(char**map, int rows, int columns, int v_pos, int h_pos, Player* players){

    if(map[v_pos][h_pos] == 'n'){ //Mur destructible
        map[v_pos][h_pos] = 'x';
        dropObject();
    }
    else if(map[v_pos][h_pos]>='1' && map[v_pos][h_pos]<='4'){ //Joueur
        takeDamage(map[v_pos][h_pos],players);
    }

    return map;
}

int checkRange(char bomb, Player * players){
    int range = 2;
    switch (bomb) {
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
    return range;
}

char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range, Player* players){

    //map[v_pos][h_pos] = 'X';
    int top_stop = 0;
    int bottom_stop = 0;
    int right_stop = 0;
    int left_stop = 0;
    char wall = 'm';

    for(int i = 1; i<=range; i++){
        if((v_pos+i) < rows){
            if(map[v_pos+i][h_pos] != '*' && map[v_pos+i][h_pos] != 'X' && map[v_pos+i][h_pos] != 'x'){
                if(map[v_pos+i][h_pos] == wall) top_stop = 1;
                else if(top_stop == 0){
                    if(map[v_pos+i][h_pos] == 'n' || (map[v_pos+i][h_pos]>='1' && map[v_pos+i][h_pos]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos+i,h_pos,players);
                    }
                    else{
                        int new_range = checkRange(map[v_pos+i][h_pos],players);
                        map = bombExplosion(map,rows,columns,v_pos+i,h_pos,new_range,players);
                        map[v_pos+i][h_pos] = 'X';
                    }
                }
            }
        }
        if((v_pos-i) >= 0){
            if(map[v_pos-i][h_pos] != '*' && map[v_pos-i][h_pos] != 'X' && map[v_pos-i][h_pos] != 'x'){
                if(map[v_pos-i][h_pos] == wall) bottom_stop = 1;
                else if(bottom_stop == 0){
                    if(map[v_pos-i][h_pos] == 'n' || (map[v_pos-i][h_pos]>='1' && map[v_pos-i][h_pos]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos-i,h_pos,players);
                    }
                    else{
                        int new_range = checkRange(map[v_pos-i][h_pos],players);
                        map = bombExplosion(map,rows,columns,v_pos-i,h_pos,new_range,players);
                        map[v_pos-i][h_pos] = 'X';
                    }
                }
            }
        }
        if((h_pos+i) < columns){
            if(map[v_pos][h_pos+i] != '*' && map[v_pos][h_pos+i] != 'X' && map[v_pos][h_pos+i] != 'x'){
                if(map[v_pos][h_pos+i] == wall) right_stop = 1;
                else if(right_stop == 0){
                    if(map[v_pos][h_pos+i] == 'n' || (map[v_pos][h_pos+i]>='1' && map[v_pos][h_pos+i]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos,h_pos+i,players);
                    }
                    else{
                        int new_range = checkRange(map[v_pos][h_pos+i],players);
                        map = bombExplosion(map,rows,columns,v_pos,h_pos+i,new_range,players);
                        map[v_pos][h_pos+i] = 'X';
                    }
                }
            }
        }
        if((h_pos-i) >= 0){
            if(map[v_pos][h_pos-i] != '*' && map[v_pos][h_pos-i] != 'X' && map[v_pos][h_pos-i] != 'x'){
                if(map[v_pos][h_pos-i] == wall) left_stop = 1;
                else if(left_stop == 0){
                    if(map[v_pos][h_pos-i] == 'n' || (map[v_pos][h_pos-i]>='1' && map[v_pos][h_pos-i]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos,h_pos-i,players);
                    }
                    else{
                        int new_range = checkRange(map[v_pos][h_pos-i],players);
                        map = bombExplosion(map,rows,columns,v_pos,h_pos-i,new_range,players);
                        map[v_pos][h_pos-i] = 'X';
                    }
                }
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
                range = checkRange(bomb_car[2],players);
                map = bombExplosion(map,rows,columns,i,y,range,players);
            }
        }
    }

    return map;
}

char** dropBomb(char**map, int v_pos, int h_pos, Player* player, char* bomb_car){

    if(map[v_pos][h_pos] == 'x'){
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
        for(int y = 0; y<columns; y++) map[i][y] = 'x';
    }

    //tests bombes:


    //map[3][4] = 'A';
    //map[3][6] = 'D';
    //map[8][9] = 'G';
    //map[1][1] = 'J';


    //map[1][7] = 'B';
    //map[9][4] = 'E';
    //map[3][4] = 'H';
    //map[9][1] = 'K';


    map[3][5] = 'C';
    map[6][10] = 'L';
    //map[0][12] = 'I';
    //map[9][2] = 'L';

    //------

    map[4][5] = 'n'; //Mur destructible
    map[5][5] = '1'; //Joueur
    map[2][5] = '2'; //Joueur
    map[3][4] = '3'; //Joueur
    map[3][6] = 'n'; //Mur destructible
    map[6][11] = 'm'; //Mur
    map[6][12] = 'm'; //Mur destructible
    map[6][7] = 'm'; //Mur
    map[6][8] = 'n'; //Mur destructible
    map[6][6] = 'n'; //Mur destructible
    map[6][5] = 'n'; //Mur destructible

    displayMap(map,rows,columns);

    char* player_1_bomb_car = "ABC";
    char* player_2_bomb_car = "DEF";
    char* player_3_bomb_car = "GHI";
    char* player_4_bomb_car = "JKL";

    displayPlayersStats(players,4);
    map = checkBombs(map,rows,columns,players,player_1_bomb_car);
    map = checkBombs(map,rows,columns,players,player_2_bomb_car);
    map = checkBombs(map,rows,columns,players,player_3_bomb_car);
    map = checkBombs(map,rows,columns,players,player_4_bomb_car);

    printf("\nNew map :\n");

    displayMap(map,rows,columns);

    displayPlayersStats(players,4);

    //map = dropBomb(map,5,7,&players[0],player_1_bomb_car);
    /*
    map = dropBomb(map,5,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,4,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,3,7,&players[0],player_1_bomb_car);
    map = dropBomb(map,2,7,&players[0],player_1_bomb_car);
    */
    //printf("\nNew map :\n");

    //displayMap(map,rows,columns);

    free(map);
}