#include <stdio.h>
#include <stdlib.h>

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
        //Autres caractères
    else {
        printf("%c", car);
    }
}

/** Affiche la carte du jeu à l'écran avec les bon caractères.
 * char **tab : le tableau de caractère du jeu.
 * int tabWidth : la largeur du tableau.
 * int tabHeight : la hauteur du tableau. */
void affTabMap(char **tab, int tabWidth, int tabHeight) {
    //Pour tout les caractère de la maps
    for(int i=0; i<tabHeight; i++) {
        for(int j=0; j<tabWidth; j++) {
            //Affiche le bon caractère à l'écran
            affCharMap(tab[i][j]);
        }
        printf("\n");
    }
}

/** Donne la position de la première map à afficher.
 * FILE *fichier : fichier de maps.
 * int nbJoueurs : nombre de joueurs -2 */
long posCurseurNbJoueurs(FILE *fichier, int nbJoueurs) {
    //Revient au début du fichier et lit la première ligne
    rewind(fichier);
    while(fgetc(fichier) != '\n');
    //Pour tout les nombres de joueurs
    for(int i=0; i<3; i++) {
        //Si l'on est pas dans la bonne section, on lit jusqu'à la prochaine section et on lit la ligne
        if(nbJoueurs != i) {
            while(fgetc(fichier) != '\t');
            while(fgetc(fichier) != '\n');
        }
            //Sinon on retourne la position du curseur
        else {
            return ftell(fichier);
        }
    }
}

/** Compte le nombre de maps pour le nombre de joueurs sélectionné.
 * FILE *fichier : fichier contenant les maps.
 * long pos : la position du curseur pour le nombre de joueurs donnés.
 * int limit : donne une limite à la lecture du fichier, -1 pour tout lire*/
int nbMaps(FILE *fichier, long pos, int limit) {
    //Positionne le curseur au bon endroit dans le fichier
    fseek(fichier, pos, SEEK_SET);

    char car1 = fgetc(fichier); //Caractère précédent
    char car2 = fgetc(fichier); //Caractère actuel
    int cmpt = 0; //compteur de maps

    //Tant que l'on est pas arrivé à la fin du fichier ou à la section suivante ou a la limite
    while(car2 != EOF && car2 != '\t' && cmpt!=limit) {
        //Si il y a eu 2 sauts de lignes d'affilé, c'est qu'on est passé à la map suivante
        if(car1 == '\n' && car2 == '\n') {
            cmpt++;
            //Lis le fichier tant qu'ils y a des sauts de lignes
            car2 = fgetc(fichier);
            while(car2 == '\n') {
                car2 = fgetc(fichier);
            }
        }
            //Sinon on passe au caractère suivant
        else {
            car1 = car2;
            car2 = fgetc(fichier);
        }
    }

    //Si la limite a été atteinte, revient aux caractères précédent afin de les lire plus tard
    if(cmpt == limit) {
        fseek(fichier, -3, SEEK_CUR);
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

/** Lis le prochain nombre depuis le curseur actuel du fichier.
 * FILE *fichier : le fichier à lire. */
int readNumber(FILE *fichier) {
    int number = 0;
    char car;
    //Lis les caractères jusqu'à tomber sur un nombre
    do {
        car = fgetc(fichier);
    } while((car<48 || car>57) && car!=EOF);

    //Transforme le caractère en nombre
    number = car-48;
    //Lis la suite des caractères et si ce sont des nombres, les ajoute à "number"
    car = fgetc(fichier);
    while(car>=48 && car<=57) {
        number *= 10;
        number += car-48;
        car = fgetc(fichier);
    }

    return number;
}

/** Initialise le jeu et retourne un tableau de chaine de caractère représentant la map de jeu (dont le pointeur a été free).
 * int *nbBombeDepart : le nombre de bombe au début du jeu.
 * int *playingMapWidth : la largeur de la map.
 * int *playingMapHeight : la hauteur de la map.
 * int *mapPrecedente : numéro de la map précédemment joué, -1 si début de partie.
 * FILE *fichier : le fichier contenant les maps du jeu.
 * long pos : la position du curseur pour le nombre de joueurs donnés.
 * int *tab : le tableau de booléen indiquant les maps sélectionnés.
 * int sizeTab : la taille du tableau tab.*/
char** initGame(int *nbBombeDepart, int *playingMapWidth, int *playingMapHeight, int *mapPrecedente, FILE *fichier, long pos, int *tab, int sizeTab) {
    //Choisi un nombre aléatoire parmis les maps sélectionnés sans que se soit la map précédente
    int randMap;
    do {
        randMap = rand() % sizeTab;
    } while(!tab[randMap] || randMap==(*mapPrecedente));

    //Si il n'y a qu'une map, ne touche pas à mapPrecedente
    if(countMapsSelected(tab, sizeTab) != 1) {
        *mapPrecedente = randMap;
    }

    //Lis le fichier jusqu'à tomber sur la map choisi aléatoirement
    nbMaps(fichier, pos, randMap);

    //Lis les nombres afin d'initialiser les données du jeu
    *nbBombeDepart = readNumber(fichier);
    *playingMapWidth = readNumber(fichier);
    *playingMapHeight = readNumber(fichier);

    //Alloue de la mémoire pour la map et entre les caractères dedans
    char car;
    char **playingMap = malloc(sizeof(char*) * (*playingMapHeight));
    for(int i=0 ; i<(*playingMapHeight); i++) {
        playingMap[i] = malloc(sizeof(char) * ((*playingMapWidth) + 1));

        car = fgetc(fichier);
        for(int j=0; j<(*playingMapWidth); j++) {
            playingMap[i][j] = car;
            car = fgetc(fichier);
        }
        while(car != '\n') {
            car = fgetc(fichier);
        }
    }

    return playingMap;
}