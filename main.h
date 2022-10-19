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