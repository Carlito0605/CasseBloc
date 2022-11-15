#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "menu.h"
#include "map.h"

int main() {
    //Gestion de l'aléatoire
    srand(time(NULL));

    //Ouvre le fichier de maps
    FILE *maps = fopen("../maps.txt", "r");
    if(maps == NULL) {
        printf("Le fichier \"maps.txt\" est introuvable.\nVeuillez verifier que ce fichier se trouve bien dans le dossier de l'executable du jeu.\n");
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
    //Gestion de la sélection menu
    int nbJoueurs = 0;

    if(menuPrincipal(&nbJoueurs, &pos, maps, &mapsSelected, &sizeMapsSelected)) {
        return 0;
    }

    //Début de la boucle de jeu
    system("cls");

    /*
    pos = posCurseurNbJoueurs(maps, nbJoueurs);
    sizeMapsSelected = 4;
    mapsSelected = malloc(sizeof(int) * sizeMapsSelected);
    for(int i=0; i<sizeMapsSelected; i++) {
        mapsSelected[i] = 1;
    }
    */

    printf("nbJoueurs=%d\nsizeMapsSelected=%d\nmapsSelected=", nbJoueurs, sizeMapsSelected);
    for(int i=0; i<sizeMapsSelected; i++) {
        printf("%d;", mapsSelected[i]);
    }
    printf("\n");
    //while(1);

    int isPlaying = 1;
    int input = 0;

    while(isPlaying) {
        playingMap = initGame(&nbBombeDepart, &playingMapWidth, &playingMapHeight, &mapPrecedente, maps, pos, mapsSelected, sizeMapsSelected);
        printf("nbBombeDepart=%d; playingMapWidth=%d; playingMapHeight=%d;\nplayingMap=\n", nbBombeDepart, playingMapWidth, playingMapHeight);
        affTabMap(playingMap, playingMapWidth, playingMapHeight);

        input = getch();
        if(input == 27) {
            isPlaying = 0;
        }

        free(playingMap);
    }
    fclose(maps);
    return 0;
}