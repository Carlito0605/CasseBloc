/*
    Autheurs : Ronan KIELT
*/

void affCharMap(char car);
void affTabMap(char **tab, int tabWidth, int tabHeight);
long posCurseurNbJoueurs(FILE *fichier, int nbJoueurs);
int nbMaps(FILE *fichier, long pos, int limit);
int countMapsSelected(int *tab, int sizeTab);
int readNumber(FILE *fichier);
char** initGame(int *nbBombeDepart, int *playingMapWidth, int *playingMapHeight, int *mapPrecedente, FILE *fichier, long pos, int *tab, int sizeTab);
