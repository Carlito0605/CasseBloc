#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/** Affiche un menu dans la console.
 * char *titre : le titre du menu.
 * char **sstitre : un tableau de sous titre.
 * int sizeSstitre : la taille du tableau de sous titre.
 * int rang : le rang actuel de la sélection de l'utilisateur (le modifie si n'est pas conforme au menu).
 * */
void menu(char *titre, char **sstitre, int sizeSstitre, int *rang) {
    system("cls");
    printf("%s\n", titre);
    if(*rang < 1) {
        *rang = 1;
    } else if(*rang > sizeSstitre) {
        *rang = sizeSstitre;
    }

    for(int i=1; i<=sizeSstitre; i++) {
        if(i == *rang) {
            printf("*");
        } else {
            printf(" ");
        }
        printf(" %s\n", sstitre[i-1]);
    }
}

/** Récupère l'appuie sur les flèche du joueur pour changer la sélection sur le menu.
 * int rang : sélection du joueur sur l'écran, un nombre entre 1 et 3 */
int changeRang(int rang) {
    int input = getch();
    switch(input) {
        //Flèche du haut
        case 72 :
            if(rang != 1) {
                return rang-1;
            }
            break;
        //Flèche du bas
        case 80 :
            if(rang != 3) {
                return rang+1;
            }
            break;
    }
    return rang;
}

/*
void affMaps(FILE *fichier, int nbJoueurs) {
    while(fgetc(fichier) != '\n');
    for(int i=1; i<=3; i++) {
        if(nbJoueurs == i) {
            break;
        } else {
            while(fgetc(fichier) != '\t');
            while(fgetc(fichier) != '\n');
        }
    }

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
*/

int main() {
    FILE *maps = fopen("maps.txt", "r");
    if(maps == NULL) {
        printf("Le fichier \"maps.txt\" est introuvable.\nVeuillez verifier que ce fichier se trouve bien dans le dossier de l'executable du jeu.\n");
        return 1;
    }

    int input;
    int rangTitre = 1;
    int rangJoueur = 1;

    int isOnTitleScreen = 1;
    int isOnSelectJoueur = 0;
    int isOnSelectMaps = 0;
    int isOnRejoindre = 0;
    int isPlaying = 0;

    while(!isPlaying) {
        system("cls");
        if(isOnTitleScreen) {
            char *ssTitre[3] = {"Solo", "Demarrer un serveur", "Rejoindre un serveur"};
            menu("CASSE BLOC", ssTitre, 3, &rangTitre);

            while(isOnTitleScreen) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    rangTitre = changeRang(rangTitre);
                    menu("CASSE BLOC", ssTitre, 3, &rangTitre);
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
            }
        }
        else if(isOnSelectJoueur) {
            char titre[] = "DEMARRER UN SERVEUR";
            if(rangTitre == 1) {
                strcpy(titre, "SOLO");
            }

            input = 0;
            char *ssJoueur[3] = {"2 Joueurs", "3 Joueurs", "4 Joueurs"};
            menu(titre, ssJoueur, 3, &rangJoueur);

            while(isOnSelectJoueur) {
                input = getch();
                //Appuie sur une flèche
                if(input == 224) {
                    rangJoueur = changeRang(rangJoueur);
                    menu(titre, ssJoueur, 3, &rangJoueur);
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
            while(fgetc(maps) != '\n');
            for(int i=1; i<=3; i++) {
                if(rangJoueur == i) {
                    break;
                } else {
                    while(fgetc(maps) != '\t');
                    while(fgetc(maps) != '\n');
                }
            }

            char car = fgetc(maps);
            while(car != EOF && car != '\t') {
                if(car >= 48 && car <= 57) {
                    printf("Nombre de bombes par joueurs : %c\n", car);
                    while(fgetc(maps) != '\n');
                    while(fgetc(maps) != '\n');
                } else {
                    printf("%c", car);
                }
                car = fgetc(maps);
            }

            while(isOnSelectMaps) {
                input = getch();
                //Touche Échap
                if(input == 27) {
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

    fclose(maps);
    while(1);
    return 0;
}