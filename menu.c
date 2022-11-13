#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <time.h>

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

/** Affiche le bon caractère à l'écran pour le caractère donné.
 * char car : le caractère à transformer. */
void affCharMap(char car) {
    //Murs
    if(car == 'm') {
        printf("%c", 177);
    } else if(car == 'x') {
        printf("%c", 219);
    }
        //Joueurs
    else if(car == 'p') {
        printf("%c", 6);
    } else if(car == '1') {
        printf("%c", 6);
    } else if(car == '2') {
        printf("%c", 3);
    } else if(car == '3') {
        printf("%c", 5);
    } else if(car == '4') {
        printf("%c", 4);
    }
        //Bombes
    else if(car=='A' || car=='D' || car=='G' || car=='J') {
        printf("%c", 207);
    } else if(car=='B' || car=='E' || car=='H' || car=='K') {
        printf("%c", 15);
    } else if(car=='C' || car=='F' || car=='I' || car=='L') {
        printf("%c", 64);
    }
        //Autres
    else {
        printf("%c", car);
    }
}

/** Affiche la carte du jeu à l'écran avec les bon caractères.
 * char **tab : le tableau de caractère du jeu.
 * int tabWidth : la largeur du tableau.
 * int tabHeight : la hauteur du tableau. */
void affTabMap(char **tab, int tabWidth, int tabHeight) {
    for(int i=0; i<tabHeight; i++) {
        for(int j=0; j<tabWidth; j++) {
            affCharMap(tab[i][j]);
        }
        printf("\n");
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
            affCharMap(car);
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
 * int nbJoueurs : nombre de joueurs -1 */
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

/** Compte le nombre de map sélectionné. Fonctionne aussi comme un booléen.
 * int *tab : le tableau de booléen.
 * int sizeTab : la taille du tableau. */
int countMapsSelected(int *tab, int sizeTab) {
    int cmpt = 0;
    for(int i=0; i<sizeTab; i++) {
        if(tab[i]) {
            cmpt += 1;
        }
    }
    return cmpt;
}

/** Initialise le jeu et retourne un tableau de chaine de caractère représentant la map de jeu.
 * int *nbBombeDepart : le nombre de bombe au début du jeu.
 * int *playingMapWidth : la largeur de la map.
 * int *playingMapHeight : la hauteur de la map.
 * FILE *fichier : le fichier contenant les maps du jeu.
 * long pos : la position du curseur pour le nombre de joueurs donnés.
 * int *tab : le tableau de booléen indiquant les maps sélectionnés.
 * int sizeTab : la taille du tableau tab.*/
char** initGame(int *nbBombeDepart, int *playingMapWidth, int *playingMapHeight, FILE *fichier, long pos, int *tab, int sizeTab) {
    fseek(fichier, pos, SEEK_SET);
    int nbMaps = countMapsSelected(tab, sizeTab);
    int randMap = (rand() % (nbMaps+1));

    int mapActuelle = 0;
    char car = fgetc(fichier);

    while(mapActuelle!=randMap && car!=EOF && car!='\t') {
        //Tant que le caractère n'est pas un nombre
        while(car<48 || car>57) {
            fgets("", 1000, fichier);
            car = fgetc(fichier);
        }

        mapActuelle++;
        if(mapActuelle!=randMap) {
            fgets("", 1000, fichier);
            fgets("", 1000, fichier);
        }
    }

    *nbBombeDepart = car-48;
    car = fgetc(fichier);
    while(car<48 || car>57) {
        car = fgetc(fichier);
    }

    *playingMapWidth = car-48;
    car = fgetc(fichier);
    while(car != ' ') {
        *playingMapWidth *= 10;
        *playingMapWidth += car-48;
        car = fgetc(fichier);
    }

    *playingMapHeight = fgetc(fichier) -48;
    car = fgetc(fichier);
    while(car != '\n') {
        *playingMapHeight *= 10;
        *playingMapHeight += car-48;
        car = fgetc(fichier);
    }

    char **playingMap = malloc(sizeof(char*) * (*playingMapHeight));
    for(int i=0 ; i<(*playingMapHeight); i++) {
        playingMap[i] = malloc(sizeof(char) * ((*playingMapWidth) + 1));

        car = fgetc(fichier);
        int j=0;
        for(int j=0; j<(*playingMapWidth); j++) {
            playingMap[i][j] = car;
            car = fgetc(fichier);
        }
        while(car != '\n') {
            car = fgetc(fichier);
        }
    }

    for(int i=0; i<(*playingMapHeight); i++) {
        for(int j=0; j<(*playingMapWidth); j++) {
            printf("%c", playingMap[i][j]);
        }
        printf("\n");
    }

    return playingMap;
}