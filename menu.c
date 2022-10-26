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

/** Affiche un menu de sélection des maps selon le nombre de joueurs sélectionnés.
 * FILE *fichier : fichier de maps.
 * long pos : la position du curseur pour le nombre de joueurs donnés.
 * int rang : le rang actuel de la sélection du joueur.
 * int *tabSelection : le tableau indiquant quels maps sont sélectionnés (1 si oui, 0 si non). */
void menuMaps(FILE *fichier, long pos, int rang, int *tabSelection) {
    system("cls");
    fseek(fichier, pos, SEEK_SET);
    char car = fgetc(fichier);
    char coche = 157;
    int cmpt = 0;
    while(car != EOF && car != '\t') {
        if(car >= 48 && car <= 57) {
            if(rang == cmpt) {
                printf("*");
            } else {
                printf(" ");
            }

            if(tabSelection[cmpt] == 1) {
                printf("%c", coche);
            } else {
                printf("O");
            }

            printf(" Nombre de bombes par joueurs : %c\n", car);
            while(fgetc(fichier) != '\n');
            while(fgetc(fichier) != '\n');
            cmpt++;
        } else {
            printf("%c", car);
        }
        car = fgetc(fichier);
    }

    if(rang == cmpt) {
        printf("*");
    } else {
        printf(" ");
    }
    printf(" Commencer la partie\n\n");
}

/** Donne la position de la première map à afficher.
 * FILE *fichier : fichier de maps.
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

/** Compte le nombre de maps pour le nombre de joueurs sélectionné.
 * FILE *fichier : fichier contenant les maps.
 * long pos : la position du curseur pour le nombre de joueurs donnés*/
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

/** Vérifie qu'au moins une map est sélectionné lors du début de la partie.
 * int *tab : le tableau de booléen.
 * int sizeTab : la taille du tableau. */
int isMapsSelected(int *tab, int sizeTab) {
    for(int i=0; i<sizeTab; i++) {
        if(tab[i]) {
            return 1;
        }
    }
    return 0;
}