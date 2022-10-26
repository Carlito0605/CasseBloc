void menu(char *titre, char **sstitre, int sizeSstitre, int rang);
void changeRang(int *rangActuel, int rangMax);
void menuMaps(FILE *fichier, long pos, int rang, int *tabSelection);
long posCurseurNbJoueurs(FILE *fichier, int nbJoueurs);
int nbMaps(FILE *fichier, long pos);
int isMapsSelected(int *tab, int sizeTab);