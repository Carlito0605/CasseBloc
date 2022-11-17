//
// Created by charl on 13/11/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "bombs.h"

void displayMap(char**map, int rows, int columns){

    /// Function that print the map using the number of rows and columns

    printf("\n");
    for(int i = -1; i<columns; i++){
        if(i!=-1) printf("_ ");
        else printf("  ");
    }
    printf("\n");
    for(int i = 0; i<rows; i++){
        printf("| ");
        for(int y = 0; y<columns; y++){
            printf("%c ",map[i][y]);
        }
        printf("|\n");
    }
    for(int i = -1; i<columns; i++){
        if(i!=-1) printf("_ ");
        else printf("  ");
    }
    printf("\n");
}

void displayMapDEBUG(char**map, int rows, int columns){

    /// Function that print the DEBUG map using the number of rows and columns

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

    /// Function that prints stats of 'n'(players_size) players in the game

    printf("\nPlayers stats :\n");
    for(int i = 0; i<players_size; i++){
        printf("* Player %d *\n",i+1);
        printf("hp : %d\n",players[i].hp);
        printf("range : %d\n",players[i].range);
        printf("current_bombs : %d\n",players[i].current_bombs);
        printf("max_bombs : %d\n",players[i].max_bombs);
        printf("max_hp : %d\n",players[i].max_hp);
        printf("bomb_special_power_up : %d\n",players[i].bomb_special_power_up);
        printf("invicibility : %d\n",players[i].invincibility);
        printf("heart : %d\n\n",players[i].heart);
    }
}

int findPlayerWithBomb(char bomb){

    ///Return the id of the owner of the bomb
    /// C -> Player 1
    /// F -> Player 2
    /// I -> Player 3
    /// L -> Player 4

    switch(bomb){
        case 'C': return 0;
        case 'F': return 1;
        case 'I': return 2;
        case 'L': return 3;
    }

    return -1;
}

void dropObject(char bomb, Player * players){

    /// This function has 1 out of n(dice_random_max) chance to drop an object
    /// Then the object is random beetween those 10 :
    /// - Bomb Up -> Add one bomb for the player
    /// - Bomb Down -> Remove one bomb of the player
    /// - Flamme Jaune -> Increase of 1 the range stat of the bomb's explosions of that player
    /// - Flamme Bleu -> Decrease of 1 the range stat of the bomb's explosions of that player
    /// - Flamme Rouge -> Max the range stat of the bomb's explosions of that player
    /// - Passe-bombes -> Put "bomb_special_power_up" at 0 for it to be used in the movement
    /// - Bomb kick -> Put "bomb_special_power_up" at 1 for it to be used in the actions
    /// - Invincibilité -> Add two turns of invincibility
    /// - Coeur -> Give a heart to the player by changing the "heart" value to 1
    ///
    /// 'bomb' is the caracter of the bomb that explosed

    //printf("\n#dropObject()\n"); //DEBUG

    int max = 100;
    int min = 0;
    int dice_random_max = 3;
    int player = findPlayerWithBomb(bomb); //check which player broke the wall

    if(player != -1){ //If he finds a player
        //printf("*** DEBUG *** -> La bombe qui explose le mur est la bombe du joueur %d !\n",player+1);
        int random = rand() % max + min;
        int dice = rand() % dice_random_max;
        if(dice == 0){
            //printf("*** DEBUG *** Random -> %d\n",random);
            if(random <= 20){ // 20% to get it
                printf("- Le Joueur *%d* ramasse 'Bomb up' !!! Il a une bombe en plus.\n",player+1);
                players[player].max_bombs++;
                players[player].current_bombs++;
            }
            if(random > 20 && random <= 40){ // 20% to get it
                printf("- Le Joueur *%d* ramasse 'Bomb down'... Il a une bombe en moins.\n",player+1);
                if(players[player].max_bombs >= 2){
                    players[player].current_bombs--;
                    players[player].max_bombs--;
                }
                else printf("** Le joueur ne peut pas avoir moins de bombes **\n");
            }
            if(random > 40 && random <= 60){ // 20% to get it
                printf("- Le Joueur *%d* ramasse 'Flamme Jaune' !!! Augmente de 1 la portée de ses bombes.\n",player+1);
                players[player].range++;
            }
            if(random > 60 && random <= 80){ // 20% to get it
                printf("- Le Joueur *%d* ramasse 'Flamme Bleu' ... Diminue de 1 la portée de ses bombes.\n",player+1);
                if(players[player].range >= 2) players[player].range--;
                else printf("** La range ne peut pas être plus baissee **\n");
            }
            if(random > 80 && random <= 82){ // 2% to get it
                printf("- LE JOUEUR *%d* RAMASSE 'FLAMME ROUGE' !!! Mets la portée de ses bombes au MAXIMUM !\n",player+1);
                players[player].range+=100000000;
            }
            if(random > 82 && random <= 87){ // 5% to get it
                printf("- Le Joueur *%d* ramasse 'Passe bombes' !!! Permet de passer à travers les bombes !",player+1);
                if(players[player].bomb_special_power_up == 1) printf("\n(Remplace 'Bomb-Kick')");
                printf("\n");
                players[player].bomb_special_power_up=0;
            }
            if(random > 87 && random <= 92){ // 5% to get it
                printf("- Le Joueur *%d* ramasse 'Bomb-Kick' !!! Permet de passer à travers les bombes !",player+1);
                if(players[player].bomb_special_power_up == 0) printf("\n(Remplace 'Passe bombes')");
                printf("\n");
                players[player].bomb_special_power_up=1;
            }
            if(random > 92 && random <= 95){ // 3% to get it
                printf("- Le Joueur *%d* ramasse 'Invincibilité' !!! Le joueur est invincible pendant 2 tours !\n",player+1);
                players[player].invincibility=2;
            }
            if(random > 95 && random <= 97){ // 2% to get it
                printf("- Le Joueur *%d* ramasse 'Coeur' !!! Vous survivrez aux prochains dégats mortels !",player+1);
                if(players[player].heart!=-1) players[player].heart=1;
                else printf("** Vous avez déjà eu un coeur cette partie ! Vous n'avez donc pas de coeur ! **");
                printf("\n");
            }
            if(random > 97 && random <= 100){ // 3% to get it
                printf("- Le Joueur *%d* ramasse 'Vie' !!! Vous gagnez 1 PV !\n",player+1);
                players[player].max_hp++;
                players[player].hp++;
            }
            //displayPlayersStats(players,4); //DEBUG
        }
    }
    else{
        printf("*** DEBUG *** -> Aucun joueur n'a été trouvé dans 'dropObject()' !\n");
        printf("*** DEBUG *** -> %c\n",bomb);
    }
}

void takeDamage(char player_number,Player * players){

    /// This function deals damage to a player hit by a bomb

    int player_id = -1;
    //printf("\n** DEBUG ** -> #takeDamage()\n");
    switch(player_number){
        case '1':
            player_id = 0;
            break;
        case '2':
            player_id = 1;
            break;
        case '3':
            player_id = 2;
            break;
        case '4':
            player_id = 3;
            break;
    }

    if(player_id != -1){
        if(players[player_id].invincibility == 0){ //Check if the player is invincible
            players[player_id].hp--;
            printf("- Le joueur *%d* prends 1 degats ! Il lui reste %d PV !\n",player_id+1,players[player_id].hp);
        }
        else printf("- Le joueur *%d* est INVINCIBLE pendant encore %d tour(s), "
                    "il ne prend donc pas de degats !\n",player_id+1,players[player_id].invincibility);
    }
    else printf("** DEBUG ** -> Il y a un problème dans la fonction 'takeDamage' player_id = -1\n");
}

char** explosionAtThatPlace(char**map, int rows, int columns, int v_pos, int h_pos, Player* players,char bomb){

    /// This function checks what it explose (Destructible wall, Player, else...)
    /// 'bomb' is the caracter of the bomb that explosed

    if(map[v_pos][h_pos] == 'm'){ //Destroyable wall
        map[v_pos][h_pos] = ' '; //Replace the wall by nothing
        //printf("\n** DEBUG ** -> BOMB : %c\n",bomb);
        dropObject(bomb,players);
    }
    else if(map[v_pos][h_pos]>='1' && map[v_pos][h_pos]<='4'){ //Player
        takeDamage(map[v_pos][h_pos],players);
    }
    else printf("** DEBUG ** -> Je ne sais pas ce que tu veux exploser calme toi !\n");

    return map;
}

int checkRange(char bomb, Player * players){

    /// This function checks the range of a bomb explosion
    /// 'bomb' is the caracter of the bomb that explosed
    /// This function also return the bomb for the player when explosed

    int range = 2;
    int player = findPlayerWithBomb(bomb);

    if(player != -1){
        range = players[player].range; //get the range of the player
        players[player].current_bombs++;  //return the bomb to the player
        if(players[player].current_bombs > players[player].max_bombs) players[player].current_bombs = players[player].max_bombs;
    }
    else{
        printf("*** DEBUG *** -> Aucun joueur n'a été trouvé dans 'checkRange()' !\n");
        printf("*** DEBUG *** -> %c\n",bomb);
    }

    return range;
}

char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range, Player* players){

    /// This function explodes the area of the bomb explosion
    /// If there is an other bomb it launch the function again
    /// If there is a desctructible wall it launch dropObject()
    /// If there is a player it launch takeDamage()
    /// If there is a wall it stop

    char bomb = map[v_pos][h_pos];
    map[v_pos][h_pos] = ' ';
    int top_stop = 0;
    int bottom_stop = 0;
    int right_stop = 0;
    int left_stop = 0;
    char wall = 'x';

    for(int i = 1; i<=range; i++){ //While we didn't reach the end of the range of the explosion
        if((v_pos+i) < rows){ //Under the bomb
            if(map[v_pos+i][h_pos] != ' '){
                if(map[v_pos+i][h_pos] == wall) top_stop = 1; //Stop to a wall
                else if(top_stop == 0){
                    if(map[v_pos+i][h_pos] == 'm' || (map[v_pos+i][h_pos]>='1' && map[v_pos+i][h_pos]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos+i,h_pos,players,bomb);
                    }
                    else{
                        int new_range = checkRange(map[v_pos+i][h_pos],players);
                        map = bombExplosion(map,rows,columns,v_pos+i,h_pos,new_range,players); //Chain explosion
                    }
                }
            }
        }
        if((v_pos-i) >= 0){ //On top of the bomb
            if(map[v_pos-i][h_pos] != ' '){
                if(map[v_pos-i][h_pos] == wall) bottom_stop = 1; //Stop to a wall
                else if(bottom_stop == 0){
                    if(map[v_pos-i][h_pos] == 'm' || (map[v_pos-i][h_pos]>='1' && map[v_pos-i][h_pos]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos-i,h_pos,players,bomb);
                    }
                    else{
                        int new_range = checkRange(map[v_pos-i][h_pos],players);
                        map = bombExplosion(map,rows,columns,v_pos-i,h_pos,new_range,players); //Chain explosion
                    }
                }
            }
        }
        if((h_pos+i) < columns){ //Right of the bomb
            if(map[v_pos][h_pos+i] != ' '){
                if(map[v_pos][h_pos+i] == wall) right_stop = 1; //Stop to a wall
                else if(right_stop == 0){
                    if(map[v_pos][h_pos+i] == 'm' || (map[v_pos][h_pos+i]>='1' && map[v_pos][h_pos+i]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos,h_pos+i,players,bomb);
                    }
                    else{
                        int new_range = checkRange(map[v_pos][h_pos+i],players);
                        map = bombExplosion(map,rows,columns,v_pos,h_pos+i,new_range,players); //Chain explosion
                    }
                }
            }
        }
        if((h_pos-i) >= 0){ //Left of the bomb
            if(map[v_pos][h_pos-i] != ' '){
                if(map[v_pos][h_pos-i] == wall) left_stop = 1; //Stop to a wall
                else if(left_stop == 0){
                    if(map[v_pos][h_pos-i] == 'm' || (map[v_pos][h_pos-i]>='1' && map[v_pos][h_pos-i]<='4')){
                        map = explosionAtThatPlace(map,rows,columns,v_pos,h_pos-i,players,bomb);
                    }
                    else{
                        int new_range = checkRange(map[v_pos][h_pos-i],players);
                        map = bombExplosion(map,rows,columns,v_pos,h_pos-i,new_range,players); //Chain explosion
                    }
                }
            }
        }
    }

    return map;
}

char** checkBombsOfOnePlayer(char**map, int rows, int columns, Player* players, char* bomb_car){

    /// This function checks the state of every bombs of one player and then goes to the next :
    /// A,D,G,J = Fresh bomb
    /// B,E,H,K = Middle time bomb
    /// C,F,I,L = Will explode next turn !

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            if(map[i][y] == bomb_car[0]){ // A,D,G,J = Fresh bomb
                map[i][y] = bomb_car[1];
            }
            else if(map[i][y] == bomb_car[1]){ // B,E,H,K = Middle time bomb
                map[i][y] = bomb_car[2];
            }
            else if(map[i][y] == bomb_car[2]){ // C,F,I,L = Will explode next turn !
                int range = checkRange(bomb_car[2],players);
                map = bombExplosion(map,rows,columns,i,y,range,players);
            }
        }
    }

    return map;
}

char** checkAllBombs(char**map, int rows, int columns, Player* players){

    ///This function checks the bombs of all the players by using checkBombsOfOnePlayer()

    map = checkBombsOfOnePlayer(map,rows,columns,players,players[0].bombs_car);
    map = checkBombsOfOnePlayer(map,rows,columns,players,players[1].bombs_car);
    map = checkBombsOfOnePlayer(map,rows,columns,players,players[2].bombs_car);
    map = checkBombsOfOnePlayer(map,rows,columns,players,players[3].bombs_car);

    return map;
}

char** dropBomb(char**map, int v_pos, int h_pos, Player* player, char* bomb_car){

    /// This function drop a bomb of a player at a demanded position

    if(map[v_pos][h_pos] == ' '){
        if(player->current_bombs > 0){
            map[v_pos][h_pos] = bomb_car[0];
            player->current_bombs--;
            printf("- Vous avez pose une bombe %c, il vous en reste %d\n",bomb_car[0],player->current_bombs);
        }
        else printf("- Vous n'avez plus assez de bombes !\n");
    }
    else printf("- Vous ne pouvez pas placer de bombe ici car : %c \n",map[v_pos][h_pos]);

    return map;
}

char** playersDeath(char** map, Player * players, int players_size){

    /// This function checks if a player is dead and delete is player symbol on the map
    /// It revives him if he have a "heart"

    for(int i = 0; i<players_size; i++){
        if(players[i].hp <= 0 && players[i].dead != 1){
            if(players[i].heart != 1){
                players[i].dead = 1;
                map[players[i].v_pos][players[i].h_pos] = ' ';
                printf("- Le joueur *%d* n'a plus de PV ! Il est donc elimine !!!\n",i+1);
            }
            else{
                players[i].heart = -1;
                printf("- Le joueur *%d* a survecu a des degats mortels grace au coeur <3 ! (Le coeur ne peut plus etre utilise)\n",i+1);
            }
        }
    }
    return map;
}

int checkIfOutOfTheMap(int rows, int columns,int v_pos,int h_pos){

    /// This function check if a bomb is out of the map and return 1 if yes 0 if no.

    //printf("\n ** DEBUG ** -> bomb_h_pos+increment=%d et columns=%d\n",h_pos,columns);
    if(v_pos <= 0 || v_pos >= rows-1) return 1;
    if(h_pos <= 0 || h_pos >= columns-1) return 1;

    return 0;
}

char** bombKick(char** map,int rows, int columns,char direction,int bomb_v_pos,int bomb_h_pos){

    /// This function move a bomb in a specified direction until it hit something using the bombs coordinates
    /// R -> Right
    /// L -> Left
    /// T -> Top
    /// B -> Bottom

    char temp_bomb_car = map[bomb_v_pos][bomb_h_pos];
    map[bomb_v_pos][bomb_h_pos] = ' ';

    int increment = 0;
    int limit = 0;

    if(direction == 'R' || direction == 'B'){
        increment = 1;
        limit = 0;
    }
    else if(direction == 'L'){
        increment = -1;
        limit = columns-1;
    }
    else if(direction == 'T'){
        increment = -1;
        limit = rows-1;
    }

    if(direction == 'R' || direction == 'L'){
        if(checkIfOutOfTheMap(rows, columns,bomb_v_pos,bomb_h_pos+increment) && map[bomb_v_pos][limit] == ' ') bomb_h_pos = limit;
        while(map[bomb_v_pos][bomb_h_pos+increment] == ' '){
            if(checkIfOutOfTheMap(rows, columns,bomb_v_pos,bomb_h_pos+increment) && map[bomb_v_pos][limit] == ' ') bomb_h_pos = limit;
            else bomb_h_pos+=increment;
        }
    }
    else if(direction == 'T' || direction == 'B'){
        if(checkIfOutOfTheMap(rows, columns,bomb_v_pos+increment,bomb_h_pos) && map[limit][bomb_h_pos] == ' ') bomb_v_pos = limit;
        while(map[bomb_v_pos+increment][bomb_h_pos] == ' '){
            if(checkIfOutOfTheMap(rows, columns,bomb_v_pos+increment,bomb_h_pos) && map[limit][bomb_h_pos] == ' ') bomb_v_pos = limit;
            else bomb_v_pos+=increment;
        }
    }

    map[bomb_v_pos][bomb_h_pos] = temp_bomb_car;

    return map;
}

void test(int rows, int columns, Player* players){

    ///Function to test that bombs are working

    char** map = malloc(sizeof (char*)*rows);
    for(int i = 0; i<rows; i++){
        map[i] = malloc(sizeof (char)*columns);
        for(int y = 0; y<columns; y++) map[i][y] = ' ';
    }

    /*

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

    map[4][5] = 'm'; //Mur destructible
    map[5][5] = '1'; //Joueur
    map[2][5] = '2'; //Joueur
    map[3][4] = '3'; //Joueur
    map[3][6] = 'm'; //Mur destructible
    map[6][11] = 'x'; //Mur
    map[6][12] = 'm'; //Mur destructible
    map[6][7] = 'x'; //Mur
    map[6][8] = 'm'; //Mur destructible
    map[6][6] = 'm'; //Mur destructible
    map[6][5] = 'm'; //Mur destructible

    displayMapDEBUG(map,rows,columns);
    displayPlayersStats(players,4);

     */

    map[3][3] = 'L';
    map[5][7] = '1';
    map[9][7] = 'x';
    map[7][3] = 'm';
    map[3][11] = 'm';
    map[3][0] = 'm';
    displayMapDEBUG(map,rows,columns);
    map = bombKick(map,rows,columns,'T',3,3);

    

    map[3][5] = 'C';
    map[3][9] = 'C';
    map[1][7] = 'C';
    map[players[1].v_pos][players[1].h_pos] = '2';

    displayMapDEBUG(map,rows,columns);

    map = checkAllBombs(map,rows,columns,players);

    printf("\nNew map :\n");

    map = playersDeath(map,players, 4);

    displayMapDEBUG(map,rows,columns);

    displayPlayersStats(players,4);

    /*

    map = dropBomb(map,5,7,&players[0],players[0].bombs_car);

    map = dropBomb(map,5,7,&players[0],players[0].bombs_car);
    map = dropBomb(map,4,7,&players[2],players[2].bombs_car);
    map = dropBomb(map,3,7,&players[2],players[2].bombs_car);
    map = dropBomb(map,2,7,&players[3],players[3].bombs_car);

    printf("\nNew map :\n");

    displayMapDEBUG(map,rows,columns);



    displayMap(map,rows,columns);

     */

    free(map);
}
