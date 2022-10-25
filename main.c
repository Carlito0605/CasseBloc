#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"
#include "move.h"

void displayMap(char **tabltest, int rows, int columns){
    for (int i=0;i<rows;i++){
        for (int j = 0; j < columns; ++j) {
            printf("%c ",tabltest[i][j]);
        }
        printf("\n");
    }
}

void move(char **tabltest,int rows, int columns, int *xmap, int *ymap, int xfuturmap, int yfuturmap){
    if(tabltest[xfuturmap][yfuturmap]!='X' && tabltest[xfuturmap][yfuturmap]!='M'){
        printf("bouge en %d:%d\n",xfuturmap,yfuturmap);
        tabltest[*xmap][*ymap] = ' ';
        tabltest[xfuturmap][yfuturmap]='P';
        *xmap=xfuturmap;
        *ymap=yfuturmap;
    }else {
        printf("impossible de bouger c'est un mur\n");

    }

}

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
            tabltest[i][j]='X';
        }

    }
    tabltest[xmap][ymap]='P';
    displayMap(tabltest,rows,columns);
    //move(tabltest, rows, columns, xmap, ymap,xmap-1,ymap);
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



    /*for(int x = 0; x< xmap;x++){
        for(int y = 0; y< ymap; y++){
            if(haut == 1 && Player[positionx][positiony + 1] == ' '){
                Player[positionx][positiony + 1];
            };
            elseif(gauche == 1 && Player[positionx - 1][positiony]== ' '){
                Player[positionx - 1][positiony];
            };

            elseif(droite == 1 && Player[positionx + 1][positiony]== ' '){
                Player[positionx + 1][positiony];
            };
            elseif(bas == 1 && Player[positionx][positiony - 1]== ' '){
                Player[positionx][positiony - 1];
            };
            if("appuie sur t"){
                dropBomb();
            }
        };
    };*/
}





