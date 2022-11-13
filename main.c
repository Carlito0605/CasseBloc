#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "menu.h"
#include <time.h>

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
    long pos = 0;
    int *mapsSelected;
    int sizeMapsSelected = 0;
    /*
    //Gestion de la sélection menu
    int input;
    int rangTitre = 0;
    int rangJoueur = 0;
    //L'ecran actuellement affiché
    int isOnTitleScreen = 1;
    int isOnSelectJoueur = 0;
    int isOnSelectMaps = 0;
    int isOnRejoindre = 0;
    int isPlaying = 0;

    //Affichage du menu principal
    while(!isPlaying) {
        system("cls");
        //Menu titre
        if(isOnTitleScreen) {
            //Crée le menu
            char *ssTitre[3] = {"Solo", "Demarrer un serveur", "Rejoindre un serveur"};
            menu("CASSE BLOC", ssTitre, 3, rangTitre);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnTitleScreen) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(&rangTitre, 3);
                    menu("CASSE BLOC", ssTitre, 3, rangTitre);
                }
                //Si touche Entrée, on change de menu
                else if(input == 13) {
                    isOnTitleScreen = 0;
                    if(rangTitre == 2) {
                        isOnRejoindre = 1;
                    } else {
                        isOnSelectJoueur = 1;
                    }
                }
                //Si touche Échap, on quitte le programme
                else if(input == 27) {
                    return 0;
                }
            }
        }
        //Menu de sélection du nombre de joueurs
        else if(isOnSelectJoueur) {
            //Affiche le bon mode de jeu
            char titre[] = "DEMARRER UN SERVEUR";
            if(rangTitre == 0) {
                strcpy(titre, "SOLO");
            }

            //Crée le menu
            char *ssJoueur[3] = {"2 Joueurs", "3 Joueurs", "4 Joueurs"};
            menu(titre, ssJoueur, 3, rangJoueur);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnSelectJoueur) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(&rangJoueur, 3);
                    menu(titre, ssJoueur, 3, rangJoueur);
                }
                //Si touche Entrée, on change de menu
                else if(input == 13) {
                    isOnSelectJoueur = 0;
                    isOnSelectMaps = 1;
                }
                //Si touche Échap, on revient au menu précédent
                else if(input == 27) {
                    isOnSelectJoueur = 0;
                    isOnTitleScreen = 1;
                }
            }
        }
        //Menu de sélection des maps
        else if(isOnSelectMaps) {
            //Récupère la position du curseur dans le fichier pour le nombre de joueurs donnés
            pos = posCurseurNbJoueurs(maps, rangJoueur);

            //Crée le tableau de maps sélectionnés et initialise les cases à 1
            sizeMapsSelected = nbMaps(maps, pos, -1);
            mapsSelected = malloc(sizeof(int) * sizeMapsSelected);
            for(int i=0; i<sizeMapsSelected; i++) {
                mapsSelected[i] = 1;
            }

            //Crée le menu
            int rangMaps = 0;
            menuMaps(maps, pos, rangMaps, mapsSelected);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnSelectMaps) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(&rangMaps, sizeMapsSelected+1);
                    menuMaps(maps, pos, rangMaps, mapsSelected);
                }
                //Touche Entrée
                else if(input == 13) {
                    //Si le joueur est sur le bouton "Commencer la partie", on vérifie qu'au moins une sélection a été faite
                    if(rangMaps == sizeMapsSelected) {
                        if(countMapsSelected(mapsSelected, sizeMapsSelected)) {
                            isOnSelectMaps = 0;
                            isPlaying = 1;
                        } else {
                            printf("Veuillez au moins selectionner une map\n");
                        }
                    } else {
                        mapsSelected[rangMaps] = !mapsSelected[rangMaps];
                        menuMaps(maps, pos, rangMaps, mapsSelected);
                    }
                }
                //Si touche Échap, on revient au menu précédent
                else if(input == 27) {
                    isOnSelectMaps = 0;
                    isOnSelectJoueur = 1;
                }
            }
        }
        //Menu pour rejoindre une partie
        else if(isOnRejoindre) {
            printf("REJOINDRE UN SERVEUR\n");

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnRejoindre) {
                input = getch();
                //Si touche Échap, on revient au menu précédent
                if(input == 27) {
                    isOnRejoindre = 0;
                    isOnTitleScreen = 1;
                }
            }
        }
    }

    //Début de la boucle de jeu
    system("cls");
    printf("Le jeu commence!\n\n");
*/

    //TEST

    pos = posCurseurNbJoueurs(maps, 0);
    sizeMapsSelected = 3;
    mapsSelected = malloc(sizeof(int) * sizeMapsSelected);
    for(int i=0; i<sizeMapsSelected; i++) {
        mapsSelected[i] = 1;
    }
    int isPlaying = 1;

    playingMap = initGame(&nbBombeDepart, &playingMapWidth, &playingMapHeight, maps, pos, mapsSelected, sizeMapsSelected);
    printf("nbBombeDepart=%d; playingMapWidth=%d; playingMapHeight=%d;\nplayingMap=\n", nbBombeDepart, playingMapWidth, playingMapHeight);

    for(int i=0; i<playingMapHeight; i++) {
       for(int j=0; j<playingMapWidth; j++) {
           printf("%c", playingMap[i][j]);
       }
       printf("\n");
    }

    fclose(maps);
    return 0;
}