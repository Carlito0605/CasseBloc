#include <stdio.h>
#include <conio.h>

/** Affiche l'écran de sélection du nombre de joueurs.
 * int rang : sélection du joueur sur l'écran, un nombre entre 1 et 3 */
void affSelectNbJoueurs(int rang) {
    if(rang == 1) {
        printf("* 2 Joueurs\n");
        printf("  3 Joueurs\n");
        printf("  4 Joueurs\n");
    } else if(rang == 2) {
        printf("  2 Joueurs\n");
        printf("* 3 Joueurs\n");
        printf("  4 Joueurs\n");
    } else if(rang == 3) {
        printf("  2 Joueurs\n");
        printf("  3 Joueurs\n");
        printf("* 4 Joueurs\n");
    }
}

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

int main() {
    int rangTitre = 1;
    char *ssTitre[3] = {"Solo", "Demarrer un serveur", "Rejoindre un serveur"};
    menu("CASSE BLOC", ssTitre, 3, &rangTitre);
    int input;
    int isOnTitleScreen = 1;

    while(isOnTitleScreen) {
        input = getch();
        //Si une flèche a été pressé
        if(input == 224) {
            rangTitre = changeRang(rangTitre);
            menu("CASSE BLOC", ssTitre, 3, &rangTitre);
        }
        //Si la touche "Entrée" est pressé
        else if(input == 13) {
            isOnTitleScreen = 0;
        }
    }
    input = 0;

    if(rangTitre == 1) {
        int rangJoueur = 1;
        char *ssJoueur[3] = {"2 Joueurs", "3 Joueurs", "4 Joueurs"};
        menu("SOLO", ssJoueur, 3, &rangJoueur);
        int isOnMenuSolo = 1;

        while(isOnMenuSolo) {
            input = getch();
            //Si une flèche a été pressé
            if(input == 224) {
                rangJoueur = changeRang(rangJoueur);
                menu("SOLO", ssJoueur, 3, &rangJoueur);
            }
            //Si la touche "Entrée" est pressé
            else if(input == 13) {
                system("cls");
                char car = 157; //Ø
                printf("O %c", car);
                isOnMenuSolo = 0;
            }
        }
    }
    else if(rangTitre == 2) {
        int port = 8080;
        int rangJoueur = 1;
        char *ssJoueur[3] = {"2 Joueurs", "3 Joueurs", "4 Joueurs"};
        menu("DEMARRER UN SERVEUR", ssJoueur, 3, &rangJoueur);
        int isOnMenuDemarrer = 1;

        while(isOnMenuDemarrer) {
            input = getch();
            //Si une flèche a été pressé
            if(input == 224) {
                rangJoueur = changeRang(rangJoueur);
                menu("DEMARRER UN SERVEUR", ssJoueur, 3, &rangJoueur);
            }
            //Si la touche "Entrée" est pressé
            else if(input == 13) {
                system("cls");
                printf("Done.");
                isOnMenuDemarrer = 0;
            }
        }
    } else if(rangTitre == 3) {
        system("cls");
        printf("REJOINDRE UN SERVEUR\n\n");
    }

    while(1);
    return 0;
}