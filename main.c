#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/** Affiche un menu dans la console.
 * char *titre : le titre du menu.
 * char **sstitre : un tableau de sous titre.
 * int sizeSstitre : la taille du tableau de sous titre.
 * int rang : le rang actuel de la sélection de l'utilisateur. */
void menu(char *titre, char **sstitre, int sizeSstitre, int rang) {
    system("cls");
    printf("%s\n", titre);

    for(int i=0; i<sizeSstitre; i++) {
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
            if(*rangActuel != 0) {
                *rangActuel -= 1;
            }
            break;
        //Flèche du bas
        case 80 :
            if(*rangActuel != rangMax-1) {
                *rangActuel += 1;
            }
            break;
    }
}

void menuMaps(FILE *fichier, long pos) {
    fseek(fichier, pos, SEEK_SET);
    char car = fgetc(fichier);
    while(car != EOF && car != '\t') {
        if(car >= 48 && car <= 57) {
            printf("Nombre de bombes par joueurs : %c\n", car);
            while(fgetc(fichier) != '\n');
            while(fgetc(fichier) != '\n');
        } else {
            printf("%c", car);
        }
        car = fgetc(fichier);
    }
}

/** Donne la position de la première map à afficher.
 * FILE *fichier : fichier sur lequel on travaille.
 * int nbJoueurs : nombre de joueurs demandé */
long posCurseurNbJoueurs(FILE *fichier, int nbJoueurs) {
    rewind(fichier);
    while(fgetc(fichier) != '\n');
    for(int i=0; i<3; i++) {
        if(nbJoueurs != i) {
            while(fgetc(fichier) != '\t');
            while(fgetc(fichier) != '\n');
        } else {
            break;
        }
    }
    return ftell(fichier);
}

int nbMaps(FILE *fichier, long pos) {
    fseek(fichier, pos, SEEK_SET);
    char car1 = fgetc(fichier);
    char car2 = fgetc(fichier);
    int cmpt = 0;
    while(car2 != '\t' && car2 != EOF) {
        if(car1 == '\n' && car2 == '\n') {
            cmpt++;
            car2 = fgetc(fichier);
            while(car2 == '\n') {
                car2 = fgetc(fichier);
            }
        } else {
            car1 = car2;
            car2 = fgetc(fichier);
        }
    }
    return cmpt;
}

int main() {
    FILE *maps = fopen("maps.txt", "r");
    if(maps == NULL) {
        printf("Le fichier \"maps.txt\" est introuvable.\nVeuillez verifier que ce fichier se trouve bien dans le dossier de l'executable du jeu.\n");
        return 1;
    }

    int input;
    int rangTitre = 0;
    int rangJoueur = 0;

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
                    if(rangTitre == 3) {
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

            menuMaps(maps, pos);

            while(isOnSelectMaps) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    changeRang(&rangMaps, sizeMapsSelected+1);
                    menuMaps(maps, pos);
                }
                //Touche Entrée
                else if(input == 13) {
                    if(rangMaps == sizeMapsSelected+1) {
                        isOnSelectMaps = 0;
                        isPlaying = 1;
                    } else {
                        mapsSelected[rangMaps] = !mapsSelected[rangMaps];
                        menuMaps(maps, pos);
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