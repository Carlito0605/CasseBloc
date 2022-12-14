/*
    Autheurs : Ronan KIELT
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "bombs.h"
#include "time.h"
#include "menu.h"
#include "map.h"

char **replacePtoPlayer(char **map, int rows, int columns) {

    /// This function replaces the 'P' caracters by 1 2 3 4 for each player

    int cmpt = 49;

    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if(map[i][j] == 'p') {
                map[i][j] = cmpt;
                cmpt++;
            }
        }
    }

    return map;
}

void findPlayerOnTheMap(char** map, int rows, int columns, int player_id, Player * players){

    /// This function finds the players caracters and update their struct positions

    int player_car = 'X';

    switch(player_id) {
        case 0 :
            player_car = '1';
            break;
        case 1 :
            player_car = '2';
            break;
        case 2 :
            player_car = '3';
            break;
        case 3 :
            player_car = '4';
            break;
    }

    if(player_car != 'X'){
        for(int i = 0; i<rows; i++){
            for(int y = 0; y<columns; y++){
                if(map[i][y] == player_car){
                    players[player_id].v_pos = i;
                    players[player_id].h_pos = y;
                    //printf("\n** DEBUG ** -> Le joueur *%d* est en [%d][%d] !\n",player_id+1,i,y);
                }
            }
        }
    }
    else printf("\n** DEBUG ** -> Il y a une erreur pour trouver le joueur, player_id = %d\n",player_id);
}

int checkIfWin(Player * players, int player_size){

    /// This function checks the number of players still alive
    /// If there is only one it return the number of the winner
    /// If there is a tie it returns 0

    int count = 0;
    for(int i = 0; i<player_size; i++) if(players[i].dead == 0) count++;
    //printf("\n** DEBUG ** -> Il y a %d joueurs en vie\n",count);
    if(count == 1){
        for(int i = 0; i<player_size; i++) if(players[i].dead == 0) return i+1;
    }
    if(count == 0) return 0;

    return -1;
}

void isOutOfTheMap(char ** map, int rows, int columns, Player * player, int v_increment, int h_increment){

    /// This function checks if the next position of a player is out of the map
    /// If it's out it replace him at the opposite side of the map if he can

    //printf("\n** DEBUG ** -> Sortie de map\n");
    int next_v = player->v_pos+v_increment;
    int next_h = player->h_pos+h_increment;
    if(next_v >= rows) next_v = 0;
    if(next_v < 0) next_v = rows-1;
    if(next_h >= columns) next_h = 0;
    if(next_h < 0) next_h = columns-1;

    if(map[next_v][next_h] == ' '){
        //printf("here");
        player->v_pos = next_v;
        player->h_pos = next_h;
    }
}

char ** movePlayer(char** map, int rows, int columns, Player * player, char direction, int player_number){

    /// This function moves a player based on the direction and his position with his struct
    /// It also launch isOutOfTheMap()
    /// If a player has 'PasseBomb' it gives him the habilities to go throught bombs

    char temp = map[player->v_pos][player->h_pos];
    map[player->v_pos][player->h_pos] = ' ';

    int v_increment = 0;
    int h_increment = 0;

    switch(direction){
        case 'L':
            h_increment--;
            break;
        case 'R':
            h_increment++;
            break;
        case 'T':
            v_increment--;
            break;
        case 'B':
            v_increment++;
            break;
    }

    if(player->v_pos+v_increment >= rows || player->v_pos+v_increment < 0 || player->h_pos+h_increment >= columns || player->h_pos+h_increment < 0){ //Sortie de map
        //printf("\n** DEBUG ** -> Sortie de map\n");
        int next_v = player->v_pos+v_increment;
        int next_h = player->h_pos+h_increment;
        if(next_v >= rows) next_v = 0;
        if(next_v < 0) next_v = rows-1;
        if(next_h >= columns) next_h = 0;
        if(next_h < 0) next_h = columns-1;

        if(map[next_v][next_h] == ' ' || map[next_v][next_h] == '#'){ //if he can go on the other side of the map
            player->v_pos = next_v;
            player->h_pos = next_h;
        }
        else if(player->bomb_special_power_up == 0 && map[next_v][next_h] >= 'A' && map[next_v][next_h] <= 'L' && (map[next_v+v_increment][next_h+h_increment] == ' ' || map[next_v][next_h] == '#')){ //if he has 'Passe-Bomb'
            printf("\n** DEBUG ** -> Passebomb + Trou de map\n");
            player->v_pos = next_v+v_increment;
            player->h_pos = next_h+h_increment;
        }
    }
    else if(player->bomb_special_power_up == 0 && map[player->v_pos+v_increment][player->h_pos+h_increment] >= 'A' && map[player->v_pos+v_increment][player->h_pos+h_increment] <= 'L'){ //if he has 'Passe-Bomb'
        printf("\n** DEBUG ** -> Passebomb\n");
        if(player->v_pos+(v_increment*2) >= rows || player->v_pos+(v_increment*2) < 0 || player->h_pos+(h_increment*2) >= columns || player->h_pos+(h_increment*2) < 0){
            isOutOfTheMap(map,rows,columns,player,(v_increment*2),(h_increment*2));
        }
        else if(map[player->v_pos+(v_increment*2)][player->h_pos+(h_increment*2)] == ' ' || map[player->v_pos+(v_increment*2)][player->h_pos+(h_increment*2)] == '#'){
            player->v_pos = player->v_pos+(v_increment*2);
            player->h_pos = player->h_pos+(h_increment*2);
        }
    }
    else if(map[player->v_pos+v_increment][player->h_pos+h_increment] != ' ' && map[player->v_pos+v_increment][player->h_pos+h_increment] != '#'){
        printf("\n** DEBUG ** -> Vous ne pouvez pas avancer la "
               "car la prochaine case est : %c\n",map[player->v_pos+v_increment][player->h_pos+h_increment]);
    }
    else{
        player->v_pos += v_increment;
        player->h_pos += h_increment;
    }

    if(map[player->v_pos][player->h_pos] == '#') dropObject(player,player_number); //If the player move on an object

    map[player->v_pos][player->h_pos] = temp;

    return map;
}

int game(char **map, int rows, int columns, int nb_bomb, int player_size) {

    /// This function is the main function where you can find the turn and action system,
    /// the results of every inputs of the users,
    /// the initialization of the players

    replacePtoPlayer(map, rows, columns);
    affTabMap(map, columns, rows);
    //displayMap(map, rows, columns);

    ///Players Inits :

    Player player_1 = {
            .hp = 1,
            .max_hp = 1,
            .max_bombs = nb_bomb,
            .range = 2,
            .current_bombs = nb_bomb,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="ABC",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_2 = {
            .hp = 1,
            .max_hp = 1,
            .max_bombs = nb_bomb,
            .range = 2,
            .current_bombs = nb_bomb,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="DEF",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_3 = {
            .hp = 1,
            .max_hp = 1,
            .max_bombs = nb_bomb,
            .range = 2,
            .current_bombs = nb_bomb,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="GHI",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player player_4 = {
            .hp = 1,
            .max_hp = 1,
            .max_bombs = nb_bomb,
            .range = 2,
            .current_bombs = nb_bomb,
            .invincibility = 0, //isn't invincible yet
            .bomb_special_power_up = -1, //don't have any special power up
            .heart=0, //didn't get a heart this game
            .bombs_car="JKL",
            .dead = 0,
            .v_pos = 0,
            .h_pos = 0
    };

    Player players[4] = {player_1, player_2, player_3, player_4};

    for (int i = 0; i < player_size; i++) findPlayerOnTheMap(map, rows, columns, i, players);

    ///START OF TURNS

    int is_playing = 1;
    int turns = 1;
    int who_is_playing = 1;
    int max_actions = 3;

    printf("\n -- TOUR(S) %d -- \n", turns);

    while (is_playing == 1) {
        for (int i = 0; i < player_size; i++) if (players[i].hp <= 0 && players[i].dead == 0) playersDeath(map, players, player_size);
        int win = checkIfWin(players, player_size);
        if (win != 0 && win != -1) {
            printf("\n\n");
            affTabMap(map, columns, rows);
            printf("\n\nLe joueur *%d* a gagne !!!!\n\n", win);
            break;
        } else if (win == 0) {
            printf("\n\n");
            affTabMap(map, columns, rows);
            printf("\n\nEGALITE\n\n");
            break;
        }

        if (players[who_is_playing - 1].dead){
            who_is_playing++;
            if(who_is_playing > player_size){
                who_is_playing = 1;
                checkAllBombs(map, rows, columns, players);
            }
        }

        printf("\nACTIONS : ");
        int player_car;
        switch(who_is_playing) {
            case 1 :
                player_car = 6;
                break;
            case 2 :
                player_car = 3;
                break;
            case 3 :
                player_car = 5;
                break;
            case 4 :
                player_car = 4;
                break;
        }
        printf("\nC'est au joueur %c de jouer ! Appuie sur 'entree' si tu es pret ! (ou 'echap' si tu veux quitter)\n", player_car);

        int temp = getch();
        if(temp != 13){
            if(temp == 27) is_playing = 0;
            else{
                while(temp != 13){
                    if(temp == 27){
                        is_playing = 0;
                        break;
                    }
                    //printf("\n** DEBUG ** -> %d\n",temp);
                    temp = getch();
                }
            }
        }
        if(is_playing != 0) {
            for(int i = max_actions; i>0; i--){
                printf("\nIl te reste %d action(s) :\n",i);
                printf("- Appuie sur les fleche directionnelles pour te deplacer\n");
                if(checkPlaceBomb(map,players[who_is_playing - 1], 'R')) {
                    printf("- Appuie sur '1' si tu veux poser une bombe a droite\n");
                }
                if(checkPlaceBomb(map,players[who_is_playing - 1], 'L')) {
                    printf("- Appuie sur '2' si tu veux poser une bombe a gauche\n");
                }
                if(checkPlaceBomb(map,players[who_is_playing - 1], 'T')) {
                    printf("- Appuie sur '3' si tu veux poser une bombe en haut\n");
                }
                if(checkPlaceBomb(map,players[who_is_playing - 1], 'B')) {
                    printf("- Appuie sur '4' si tu veux poser une bombe en bas\n");
                }
                if (checkBombKick(map, players[who_is_playing - 1], 'R')) {
                    printf("- Appuie sur '5' si tu kick une bombe a droite\n");
                }
                if (checkBombKick(map, players[who_is_playing - 1], 'L')) {
                    printf("- Appuie sur '6' si tu kick une bombe a gauche\n");
                }
                if (checkBombKick(map, players[who_is_playing - 1], 'T')) {
                    printf("- Appuie sur '7' si tu kick une bombe en haut\n");
                }
                if (checkBombKick(map, players[who_is_playing - 1], 'B')) {
                    printf("- Appuie sur '8' si tu kick une bombe en bas\n");
                }

                printf("- Appuie sur 'echap' si tu veux quitter la partie.\n");
                printf("- Sinon, appuyez sur n'importe quel autre touche pour passer votre tour\n\n");

                temp = getch();

                system("cls");

                printf("\nINFOS : \n");

                //V??rifie qu'une fl??che a ??t?? press??
                switch (temp) {
                    case 224 :
                        temp = getch();
                        //V??rifie quelle fl??che a ??t?? press??e
                        switch (temp) {
                            case 72 :
                                printf("- Vous avancez en haut\n");
                                movePlayer(map, rows, columns, &players[who_is_playing - 1], 'T',who_is_playing);
                                break;
                            case 80 :
                                printf("- Vous avancez en bas\n");
                                movePlayer(map, rows, columns, &players[who_is_playing - 1], 'B',who_is_playing);
                                break;
                            case 75 :
                                printf("- Vous avancez a gauche\n");
                                movePlayer(map, rows, columns, &players[who_is_playing - 1], 'L',who_is_playing);
                                break;
                            case 77 :
                                printf("- Vous avancez a droite\n");
                                movePlayer(map, rows, columns, &players[who_is_playing - 1], 'R',who_is_playing);
                                break;
                        }
                        break;
                    case 27 : // -> echap
                        is_playing = 0;
                        break;
                    case 49 : // -> 1 -> Drop a bomb to the right
                        if(checkPlaceBomb(map,players[who_is_playing - 1], 'R'))
                            map = dropBomb(map, players[who_is_playing - 1].v_pos, players[who_is_playing - 1].h_pos + 1,
                                       &players[who_is_playing - 1], players[who_is_playing - 1].bombs_car);
                        break;
                    case 50 : // -> 2 -> Drop a bomb to the left
                        if(checkPlaceBomb(map, players[who_is_playing - 1], 'L'))
                            map = dropBomb(map, players[who_is_playing - 1].v_pos, players[who_is_playing - 1].h_pos - 1,
                                       &players[who_is_playing - 1], players[who_is_playing - 1].bombs_car);
                        break;
                    case 51 : // -> 3 -> Drop a bomb above
                        if(checkPlaceBomb(map, players[who_is_playing - 1], 'T'))
                            map = dropBomb(map, players[who_is_playing - 1].v_pos - 1, players[who_is_playing - 1].h_pos,
                                       &players[who_is_playing - 1], players[who_is_playing - 1].bombs_car);
                        break;
                    case 52 : // -> 4 -> Drop a bomb under
                        if(checkPlaceBomb(map, players[who_is_playing - 1], 'B'))
                            map = dropBomb(map, players[who_is_playing - 1].v_pos + 1, players[who_is_playing - 1].h_pos,
                                       &players[who_is_playing - 1], players[who_is_playing - 1].bombs_car);
                        break;
                    case 53 : // -> 5 -> Kick a bomb to the right
                        if (checkBombKick(map, players[who_is_playing - 1], 'R'))
                            map = bombKick(map, rows, columns, 'R', players[who_is_playing - 1].v_pos,
                                           players[who_is_playing - 1].h_pos + 1);
                        break;
                    case 54 : // -> 6 -> Kick a bomb to the left
                        if (checkBombKick(map, players[who_is_playing - 1], 'L'))
                            map = bombKick(map, rows, columns, 'L', players[who_is_playing - 1].v_pos,
                                           players[who_is_playing - 1].h_pos - 1);
                        break;
                    case 55 : // -> 7 -> Kick a bomb to the top
                        if (checkBombKick(map, players[who_is_playing - 1], 'T'))
                            map = bombKick(map, rows, columns, 'T', players[who_is_playing - 1].v_pos - 1,
                                           players[who_is_playing - 1].h_pos);
                        break;
                    case 56 : // -> 8 -> Kick a bomb to the bottom
                        if (checkBombKick(map, players[who_is_playing - 1], 'B'))
                            map = bombKick(map, rows, columns, 'B', players[who_is_playing - 1].v_pos + 1,
                                           players[who_is_playing - 1].h_pos);
                        break;
                    default :
                        printf("- Vous avez passe votre tour\n");
                        i=1;
                        break;
                }

                if(i != 1) {
                    printf("\n");
                    affTabMap(map, columns, rows);
                }
            }

            for (int i = 0; i < player_size; i++) {
                if (players[i].invincibility > 0) {
                    players[i].invincibility--;
                    printf("- Il reste %d tours d'invincibilite au joueur %d\n", players[i].invincibility, i + 1);
                }
            }

            who_is_playing++;
            if (who_is_playing > player_size) {
                who_is_playing = 1;
                checkAllBombs(map, rows, columns, players);
            }

            turns++;
            printf("\n");
            affTabMap(map, columns, rows);
            printf("\n - - TOUR(S) %d -- \n", turns);

            if (who_is_playing == 1) {
                clearExplosions(map,rows,columns);
            }
        }
    }

    return 0;
}

int main(){
    //Gestion de l'al??atoire
    srand(time(NULL));
    
    //Ouvre le fichier de maps
    FILE *maps = fopen("../maps.txt", "r");
    if(maps == NULL) {
        printf("Le fichier \"maps.txt\" est introuvable.\nVeuillez verifier que ce fichier se trouve bien dans le dossier du code source du jeu.\n");
        return 1;
    }
    //Variables de jeu
    int nbBombeDepart = 0;
    int playingMapWidth = 0;
    int playingMapHeight = 0;
    char **playingMap;
    int mapPrecedente = -1;
    long pos = 0;
    int *mapsSelected;
    int sizeMapsSelected = 0;
    //Gestion de la s??lection menu
    int nbJoueurs = 0;

    if(menuPrincipal(&nbJoueurs, &pos, maps, &mapsSelected, &sizeMapsSelected)) {
        return 0;
    }

    //D??but de la boucle de jeu
    system("cls");

    int isPlaying = 1;
    int input = 0;

    while(isPlaying) {
        playingMap = initGame(&nbBombeDepart, &playingMapWidth, &playingMapHeight, &mapPrecedente, maps, pos, mapsSelected, sizeMapsSelected);
        //printf("nbBombeDepart=%d; playingMapWidth=%d; playingMapHeight=%d;\nplayingMap=\n", nbBombeDepart, playingMapWidth, playingMapHeight);
        //affTabMap(playingMap, playingMapWidth, playingMapHeight);

        game(playingMap, playingMapHeight, playingMapWidth, nbBombeDepart, nbJoueurs+2);

        printf("\nAppuyez sur n'importe quel touche pour recommencer\n");
        printf("Appuyez sur Echap ou 0 pour quitter le jeu\n");

        input = getch();
        if(input == 27 || input == 48) {
            isPlaying = 0;
        }
        system("cls");

        free(playingMap);
    }
    fclose(maps);

    return 0;
}