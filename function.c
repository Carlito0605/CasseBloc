#include <stdio.h>
#include "main.h"
#include "function.h"
void move(char **tabltest,int rows, int columns, int *xmap, int *ymap, int xfuturmap, int yfuturmap) {
    if (xfuturmap <= rows && yfuturmap <= columns) {
        switch (tabltest[xfuturmap][yfuturmap]) {
            case 'X':
                printf("impossible de bouger c'est un mur\n");
                break;
            case 'M':
                printf("impossible de bouger c'est un mur\n");
                break;
            case 'A':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'B':
                printf("impossible de bouger c'est une bombe incendiaire\n");
                break;
            case 'C':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'D':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'E':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'F':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'G':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'H':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'I':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'J':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'K':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case 'L':
                printf("impossible de bouger c'est une bombe\n");
                break;
            case '0':
                printf("bouge en %d:%d\n", xfuturmap, yfuturmap);
                tabltest[*xmap][*ymap] = '0';
                tabltest[xfuturmap][yfuturmap] = 'P';
                *xmap = xfuturmap;
                *ymap = yfuturmap;
                break;
            default:
                printf("impossible de bouger l'endoit ou vous souhaitez aller n'est pas possible\n");
                break;
        }
    }
    if (xfuturmap > rows) {
        *xmap = 0;
        *ymap = yfuturmap;
        printf("bouge en %d:%d\n", xfuturmap, yfuturmap);
        tabltest[*xmap][*ymap] = '0';
        tabltest[xfuturmap][yfuturmap] = 'P';

    }
    if (yfuturmap > columns) {
        *xmap = xfuturmap;
        *ymap = 0;
        printf("bouge en %d:%d\n", xfuturmap, yfuturmap);
        tabltest[*xmap][*ymap] = '0';
        tabltest[xfuturmap][yfuturmap] = 'P';
    }
    if (xfuturmap <0 ) {
        *xmap = rows;
        *ymap = yfuturmap;
        printf("bouge en %d:%d\n", xfuturmap, yfuturmap);
        tabltest[*xmap][*ymap] = '0';
        tabltest[xfuturmap][yfuturmap] = 'P';
    }
    if (yfuturmap < 0) {
        *xmap = xfuturmap;
        *ymap = columns;
        printf("bouge en %d:%d\n", xfuturmap, yfuturmap);
        tabltest[*xmap][*ymap] = '0';
        tabltest[xfuturmap][yfuturmap] = 'P';
    }
}
void displayMap(char **tabltest, int rows, int columns){
    for (int i=0;i<rows;i++){
        for (int j = 0; j < columns; ++j) {
            printf("%c ",tabltest[i][j]);
        }
        printf("\n");
    }
}