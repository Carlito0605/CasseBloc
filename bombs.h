#include "main.h"

void displayMap(char**map, int rows, int columns){
    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            printf("%c ",map[i][y]);
        }
        printf("\n");
    }
}

char** checkBombs(char**map, int rows, int columns){

    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            switch(map[i][y]){
                case '3':
                    map[i][y] = '4';
                    break;
                case '4':
                    map[i][y] = '5';
                    break;
                case '5':
                    map[i][y] = 'X';
                    break;
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