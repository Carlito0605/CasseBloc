typedef struct bomb{
    int range;
    int current_timer;
}Bomb;

typedef struct player{
    int hp;
    int max_hp;
    Bomb* bombs;
    int max_bombs;
}Player;

void displayMap(char**map, int rows, int columns){
    for(int i = 0; i<rows; i++){
        for(int y = 0; y<columns; y++){
            printf("%c ",map[i][y]);
        }
        printf("\n");
    }
}



void test(int rows, int columns){

    char** map = malloc(sizeof (char*)*rows);
    for(int i = 0; i<rows; i++){
        map[i] = malloc(sizeof (char)*columns);
        for(int y = 0; y<columns; y++) map[i][y] = '.';
    }

    map[3][4] = '3';
    map[2][7] = '3';
    map[3][6] = '3';
    map[7][4] = '3';
    map[8][9] = '3';
    map[1][1] = '3';

    displayMap(map,rows,columns);

    //checkBombs();

    printf("test");
    free(map);
}