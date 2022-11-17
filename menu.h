void menu(char *titre, char **sstitre, int sizeSstitre, int rang);
void changeRang(int *rangActuel, int rangMax);
void menuMaps(FILE *fichier, long pos, int rang, int *tabSelection);
int menuPrincipal(int *rangJoueur, long *pos, FILE *maps, int **mapsSelected, int *sizeMapsSelected);
