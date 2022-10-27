#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"
#include "function.h"
int main() {
    int xmap = 2;
    int ymap = 2;
    int rows = 5;
    int columns = 5;
    char ** tabltest = malloc(sizeof (char*)*rows);
    for (int i = 0; i < rows; ++i) {
        tabltest[i]= malloc(sizeof (char)*columns);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tabltest[i][j]='0';
        }
    }
    tabltest[xmap][ymap]='P';
    displayMap(tabltest,rows,columns);
    printf("\n");

    while(1) {
        int input = getch();
        //Vérifie qu'une flèche a été pressé
        if(input == 224) {
            input = getch();
            //Vérifie quel flèche a été pressé
            switch(input) {
                case 72 :
                    printf("haut\n");
                    move(tabltest, rows, columns, &xmap, &ymap,xmap-1,ymap);
                    displayMap(tabltest,rows,columns);
                    break;
                case 80 :
                    printf("bas\n");
                    move(tabltest, rows, columns, &xmap, &ymap,xmap+1,ymap);
                    displayMap(tabltest,rows,columns);
                    break;
                case 75 :
                    printf("gauche\n");
                    move(tabltest, rows, columns, &xmap, &ymap,xmap,ymap-1);
                    displayMap(tabltest,rows,columns);
                    break;
                case 77 :
                    printf("droite\n");
                    move(tabltest, rows, columns, &xmap, &ymap,xmap,ymap+1);
                    displayMap(tabltest,rows,columns);
                    break;
            }
        }
        input = 0;
    }
}





