typedef struct {
    int range;
    int current_timer;
}Bomb;
typedef struct
{
    int hp;
    int max_hp;
    Bomb* bombs;
    int max_bombs;
} Player;