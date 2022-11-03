#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "menu.h"

int main() {
    FILE *maps = fopen("maps.txt", "r");
    if(maps == NULL) {
        printf("Le fichier \"maps.txt\" est introuvable.\nVeuillez verifier que ce fichier se trouve bien dans le dossier de l'executable du jeu.\n");
        return 1;
    }
    //Variables de jeu
    int nbBombeDepart = 0;
    int playingMapWidth = 0;
    int playingMapLenght = 0;
    char **playingMap;
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

    while(!isPlaying) {
        system("cls");
        if(isOnTitleScreen) {
            char *ssTitre[3] = {"Solo", "Demarrer un serveur", "Rejoindre un serveur"};
            menu("CASSE BLOC", ssTitre, 3, rangTitre);

            while(isOnTitleScreen) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    changeRang(&rangTitre, 3);
                    menu("CASSE BLOC", ssTitre, 3, rangTitre);
                }
                //Touche Entrée
                else if(input == 13) {
                    isOnTitleScreen = 0;
                    if(rangTitre == 2) {
                        isOnRejoindre = 1;
                    } else {
                        isOnSelectJoueur = 1;
                    }
                }
                //Touche Échap
                else if(input == 27) {
                    return 0;
                }
            }
        }
        else if(isOnSelectJoueur) {
            char titre[] = "DEMARRER UN SERVEUR";
            if(rangTitre == 0) {
                strcpy(titre, "SOLO");
            }

            input = 0;
            char *ssJoueur[3] = {"2 Joueurs", "3 Joueurs", "4 Joueurs"};
            menu(titre, ssJoueur, 3, rangJoueur);

            while(isOnSelectJoueur) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    changeRang(&rangJoueur, 3);
                    menu(titre, ssJoueur, 3, rangJoueur);
                }
                //Touche Entrée
                else if(input == 13) {
                    isOnSelectJoueur = 0;
                    isOnSelectMaps = 1;
                }
                //Touche Échap
                else if(input == 27) {
                    isOnSelectJoueur = 0;
                    isOnTitleScreen = 1;
                }
            }
        }
        else if(isOnSelectMaps) {
            long pos = posCurseurNbJoueurs(maps, rangJoueur);
            int sizeMapsSelected = nbMaps(maps, pos);
            int mapsSelected[sizeMapsSelected];
            for(int i=0; i<sizeMapsSelected; i++) {
                mapsSelected[i] = 1;
            }
            int rangMaps = 0;

            menuMaps(maps, pos, rangMaps, mapsSelected);

            while(isOnSelectMaps) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    changeRang(&rangMaps, sizeMapsSelected+1);
                    menuMaps(maps, pos, rangMaps, mapsSelected);
                }
                //Touche Entrée
                else if(input == 13) {
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
                //Touche Échap
                else if(input == 27) {
                    isOnSelectMaps = 0;
                    isOnSelectJoueur = 1;
                }
            }
        }
        else if(isOnRejoindre) {
            printf("REJOINDRE UN SERVEUR\n");

            while(isOnRejoindre) {
                input = getch();
                //Touche Échap
                if(input == 27) {
                    isOnRejoindre = 0;
                    isOnTitleScreen = 1;
                }
            }
        }
    }

    system("cls");
    printf("Le jeu commence!\n");

    fclose(maps);
    while(1);
    return 0;
}