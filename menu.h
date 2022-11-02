void menu(char *titre, char **sstitre, int sizeSstitre, int rang);
void changeRang(int *rangActuel, int rangMax);
void affCharMap(char car);
void affTabMap(char **tab, int tabWidth, int tabHeight);
void menuMaps(FILE *fichier, long pos, int rang, int *tabSelection);
long posCurseurNbJoueurs(FILE *fichier, int nbJoueurs);
int nbMaps(FILE *fichier, long pos);
int isMapsSelected(int *tab, int sizeTab);