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

/** Récupère l'appuie sur les flèche du joueur pour changer la sélection sur le menu titre.
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
    int rang = 1;
    affEcranTitre(rang);
    int input = getch();
    int isOnTitleScreen = 1;

    while(isOnTitleScreen) {
        //Si une flèche a été pressé
        if(input == 224) {
            rang = changeRang(rang);
            affEcranTitre(rang);
            input = getch();
        }
        //Si la touche "Entrée" est pressé
        else if(input == 13) {
            isOnTitleScreen = 0;
        }
    }

    system("cls");
    if(rang == 1) {
        printf("SOLO\n");
    } else if(rang == 2) {
        int port = 8080;
        printf("DEMARRER UN SERVEUR\n");
    } else if(rang == 3) {
        printf("REJOINDRE UN SERVEUR\n");
    }
    while(1);

    return 0;
}