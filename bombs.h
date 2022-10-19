#include "main.h"

void displayMap(char**map, int rows, int columns){
    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            printf("%c ",map[i][y]);
        }
        printf("\n");
    }
}

char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range){

    map[v_pos][h_pos] = 'X';

    for(int i = 1; i<=range; i++){
        if((v_pos+i) < rows) map[v_pos+i][h_pos] = '*';
        if((v_pos-i) >= 0) map[v_pos-i][h_pos] = '*';
        if((h_pos+i) < columns) map[v_pos][h_pos+i] = '*';
        if((h_pos-i) >= 0) map[v_pos][h_pos-i] = '*';
    }

    return map;
}

char** checkBombs(char**map, int rows, int columns){

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            if(map[i][y] == '3'){
                map[i][y] = '4';
            }
            else if(map[i][y] == '4'){
                map[i][y] = '5';
            }
            else if(map[i][y] == '5'){
                //map[i][y] = 'X';
                map = bombExplosion(map,rows,columns,i,y,2);
            }
        }
    }

    return map;
}

void test(int rows, int columns, Player* players){

    char** map = malloc(sizeof (char*)*rows);
    for(int i = 0; i<rows; i++){
        map[i] = malloc(sizeof (char)*columns);
        for(int y = 0; y<columns; y++) map[i][y] = '.';
    }

    map[3][4] = '3';
    map[2][7] = '3';
    map[3][6] = '3';
    map[7][4] = '3';
    map[8][9] = '3';
    map[1][1] = '3';
    map[1][7] = '4';
    map[9][4] = '4';
    map[3][4] = '4';
    map[9][1] = '4';
    map[3][0] = '5';
    map[9][11] = '5';
    map[5][14] = '5';
    map[6][9] = '5';

    displayMap(map,rows,columns);

    map = checkBombs(map,rows,columns);

    printf("\nNew map :\n");

    displayMap(map,rows,columns);

    printf("test");
    free(map);
}