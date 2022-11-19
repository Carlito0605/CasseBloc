#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "map.h"

/** Affiche un menu dans la console.
 * char *titre : le titre du menu.
 * char **sstitre : un tableau de sous titre.
 * int sizeSstitre : la taille du tableau de sous titre.
 * int rang : le rang actuel de la sélection de l'utilisateur. */
void menu(char *titre, char **sstitre, int sizeSstitre, int rang) {
    //Efface l'écran et affiche le titre du menu
    system("cls");
    printf("%s\n", titre);

    //Affiche les sous-titres
    for(int i=0; i<sizeSstitre; i++) {
        //Si le sous-titre actuel est sélectionné, affiche le caractère "*"
        if(i == rang) {
            printf("*");
        } else {
            printf(" ");
        }
        printf(" %s\n", sstitre[i]);
    }
}

/** Récupère l'appuie sur les flèche du joueur pour changer la sélection sur le menu.
 * int rangActuel : sélection du joueur sur l'écran, un nombre entre 0 et rangMax.
 * int rangMax : le nombre de sous menu. */
void changeRang(int *rangActuel, int rangMax) {
    int input = getch();
    switch(input) {
        //Flèche du haut
        case 72 :
            //Gère le cas où la sélection est déjà tout en haut
            if(*rangActuel != 0) {
                *rangActuel -= 1;
            }
            break;
        //Flèche du bas
        case 80 :
            //Gère le cas où la sélection est déjà tout en bas
            if(*rangActuel != rangMax-1) {
                *rangActuel += 1;
            }
            break;
    }
}

/** Affiche un menu de sélection des maps selon le nombre de joueurs sélectionnés.
 * FILE *fichier : fichier de maps.
 * long pos : la position du curseur pour le nombre de joueurs donnés.
 * int rang : le rang actuel de la sélection du joueur.
 * int *tabSelection : le tableau indiquant quels maps sont sélectionnés (1 si oui, 0 si non). */
void menuMaps(FILE *fichier, long pos, int rang, int *tabSelection) {
    //Efface l'écran et positionne le curseur au bon endroit dans le fichier
    system("cls");
    fseek(fichier, pos, SEEK_SET);

    char car = fgetc(fichier); //Caractère actuel dans le fichier
    char coche = 157; //caractère "Ø"
    int cmpt = 0; //Compteur du nombre de maps rencontré dans la boucle

    //Tant que l'on est pas arrivé à la fin du fichier ou à la section suivante
    while(car != EOF && car != '\t') {
        //Si le caractère est un nombre
        if(car >= 48 && car <= 57) {
            //Si le curseur est sur la map actuelle, affiche un "*"
            if(rang == cmpt) {
                printf("*");
            } else {
                printf(" ");
            }

            //Si la map est sélectionné, affiche "Ø" sinon "O"
            if(tabSelection[cmpt] == 1) {
                printf("%c", coche);
            } else {
                printf("O");
            }

            //Affiche le nombre de bombe par joueur puis lis 2 lignes entières pour passer à l'affichage de la map
            printf(" Nombre de bombes par joueurs : %c\n", car);
            while(fgetc(fichier) != '\n');
            while(fgetc(fichier) != '\n');
            //Incrémente le compteur de maps rencontrés
            cmpt++;
        }
        //Si le caractère n'est pas un nombre, l'affiche à l'écran avec la bonne syntaxe
        else {
            affCharMap(car);
        }
        car = fgetc(fichier);
    }

    //Si le curseur est sur "Commencer la partie", on affiche "*"
    if(rang == cmpt) {
        printf("*");
    } else {
        printf(" ");
    }
    printf(" Commencer la partie\n\n");
}

/** Affiche le menu principal du jeu.
 * Retourne 0 si le joueur joue, 1 sinon.
 * int *rangJoueur : le nombre de joueurs -2.
 * long *pos : la position du curseur selon le nombre de joueurs.
 * FILE *maps : le fichier contenant les maps.
 * int **mapsSelected : le tableau de booléen indiquant les maps sélectionnés.
 * int *sizeMapsSelected : la taille du tableau de maps sélectionnés.*/
int menuPrincipal(int *rangJoueur, long *pos, FILE *maps, int **mapsSelected, int *sizeMapsSelected) {
    //L'ecran actuellement affiché
    int isOnTitleScreen = 1;
    int isOnSelectJoueur = 0;
    int isOnSelectMaps = 0;
    int isOnRejoindre = 0;

    int input;
    int rangTitre = 0;

    while(1) {
        system("cls");
        //Menu titre
        if(isOnTitleScreen) {
            //Crée le menu
            char *ssTitre[3] = {"Solo", "Demarrer un serveur", "Rejoindre un serveur"};
            menu("                                                                                        \n"
                 "     _/_/_/                                              _/_/_/    _/                   \n"
                 "  _/          _/_/_/    _/_/_/    _/_/_/    _/_/        _/    _/  _/    _/_/      _/_/_/\n"
                 " _/        _/    _/  _/_/      _/_/      _/_/_/_/      _/_/_/    _/  _/    _/  _/       \n"
                 "_/        _/    _/      _/_/      _/_/  _/            _/    _/  _/  _/    _/  _/        \n"
                 " _/_/_/    _/_/_/  _/_/_/    _/_/_/      _/_/_/      _/_/_/    _/    _/_/      _/_/_/   \n"
                 "                                                                                        \n"
                 "                                                                                        ", ssTitre, 3, rangTitre);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnTitleScreen) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(&rangTitre, 3);
                    menu("                                                                                        \n"
                         "     _/_/_/                                              _/_/_/    _/                   \n"
                         "  _/          _/_/_/    _/_/_/    _/_/_/    _/_/        _/    _/  _/    _/_/      _/_/_/\n"
                         " _/        _/    _/  _/_/      _/_/      _/_/_/_/      _/_/_/    _/  _/    _/  _/       \n"
                         "_/        _/    _/      _/_/      _/_/  _/            _/    _/  _/  _/    _/  _/        \n"
                         " _/_/_/    _/_/_/  _/_/_/    _/_/_/      _/_/_/      _/_/_/    _/    _/_/      _/_/_/   \n"
                         "                                                                                        \n"
                         "                                                                                        ", ssTitre, 3, rangTitre);
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
                    return 1;
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
            menu(titre, ssJoueur, 3, *rangJoueur);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnSelectJoueur) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(rangJoueur, 3);
                    menu(titre, ssJoueur, 3, *rangJoueur);
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
            *pos = posCurseurNbJoueurs(maps, *rangJoueur);

            //Crée le tableau de maps sélectionnés et initialise les cases à 1
            *sizeMapsSelected = nbMaps(maps, *pos, -1);
            *mapsSelected = malloc(sizeof(int) * (*sizeMapsSelected));
            for(int i=0; i<(*sizeMapsSelected); i++) {
                (*mapsSelected)[i] = 1;
            }

            //Crée le menu
            int rangMaps = 0;
            menuMaps(maps, *pos, rangMaps, *mapsSelected);

            //Tant que l'utilisateur ne change pas de menu, on récupère ses input
            while(isOnSelectMaps) {
                input = getch();
                //Appuie sur une flèche pour changer la sélection
                if(input == 224) {
                    changeRang(&rangMaps, (*sizeMapsSelected)+1);
                    menuMaps(maps, *pos, rangMaps, *mapsSelected);
                }
                    //Touche Entrée
                else if(input == 13) {
                    //Si le joueur est sur le bouton "Commencer la partie", on vérifie qu'au moins une sélection a été faite
                    if(rangMaps == *sizeMapsSelected) {
                        if(countMapsSelected(*mapsSelected, *sizeMapsSelected)) {
                            return 0;
                        } else {
                            printf("Veuillez au moins selectionner une map\n");
                        }
                    }
                    //Si le joueur est sur un autre bouton, on change la sélection
                    else {
                        (*mapsSelected)[rangMaps] = !(*mapsSelected)[rangMaps];
                        menuMaps(maps, *pos, rangMaps, *mapsSelected);
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
}