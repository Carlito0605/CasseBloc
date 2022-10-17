#include <stdio.h>
#include <conio.h>

/** Affiche l'écran titre.
 * int rang : sélection du joueur sur l'écran, un nombre entre 1 et 3 */
void affEcranTitre(int rang) {
    system("cls");
    printf("CASSE BLOC\n");
    if(rang == 1) {
        printf("* Solo\n");
        printf("  Demarrer un serveur\n");
        printf("  Rejoindre un serveur\n");
    } else if(rang == 2) {
        printf("  Solo\n");
        printf("* Demarrer un serveur\n");
        printf("  Rejoindre un serveur\n");
    } else if(rang == 3) {
        printf("  Solo\n");
        printf("  Demarrer un serveur\n");
        printf("* Rejoindre un serveur\n");
    }
}

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
    affEcranTitre(rangTitre);
    int input;
    int isOnTitleScreen = 1;

    while(isOnTitleScreen) {
        input = getch();
        //Si une flèche a été pressé
        if(input == 224) {
            rangTitre = changeRang(rangTitre);
            affEcranTitre(rangTitre);
        }
        //Si la touche "Entrée" est pressé
        else if(input == 13) {
            isOnTitleScreen = 0;
        }
    }

    system("cls");
    int rangJoueur = 1;
    input = 0;

    if(rangTitre == 1) {
        int isOnMenuSolo = 1;
        printf("SOLO\n");
        affSelectNbJoueurs(rangJoueur);
        while(isOnMenuSolo) {
            input = getch();
            //Si une flèche a été pressé
            if(input == 224) {
                system("cls");
                printf("SOLO\n");
                rangJoueur = changeRang(rangJoueur);
                affSelectNbJoueurs(rangJoueur);
            }
            //Si la touche "Entrée" est pressé
            else if(input == 13) {
                system("cls");
                printf("Done.");
                isOnMenuSolo = 0;
            }
        }
    }
    else if(rangTitre == 2) {
        int port = 8080;
        int isOnMenuDemarrer = 1;
        printf("DEMARRER UN SERVEUR\n");
        affSelectNbJoueurs(rangJoueur);
        while(isOnMenuDemarrer) {
            input = getch();
            //Si une flèche a été pressé
            if(input == 224) {
                system("cls");
                printf("DEMARRER UN SERVEUR\n");
                rangJoueur = changeRang(rangJoueur);
                affSelectNbJoueurs(rangJoueur);
            }
            //Si la touche "Entrée" est pressé
            else if(input == 13) {
                system("cls");
                printf("Done.");
                isOnMenuDemarrer = 0;
            }
        }
    } else if(rangTitre == 3) {
        printf("REJOINDRE UN SERVEUR\n\n");
    }

    while(1);
    return 0;
}