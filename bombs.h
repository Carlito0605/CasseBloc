//
// Created by charl on 13/11/2022.
//

typedef struct player{
    int hp;
    int max_hp;
    int current_bombs;
    int max_bombs;
    int range;
    int bomb_special_power_up; //-1=rien, 0=Passe bomb, 1=Bomb kick
    int invincibility; //tours restants d'invincibilité
    int heart; //-1=coeur déjà utilisé, 0=pas de coeur, 1=a un coeur
    char* bombs_car;
}Player;

void displayMap(char**map, int rows, int columns);
void displayPlayersStats(Player * players,int players_size);
int findPlayerWithBomb(char bomb);
void dropObject(char bomb, Player * players);
void takeDamage(char player_number,Player * players);
char** explosionAtThatPlace(char**map, int rows, int columns, int v_pos, int h_pos, Player* players,char bomb);
int checkRange(char bomb, Player * players);
char** bombExplosion(char**map, int rows, int columns, int v_pos, int h_pos, int range, Player* players);
char** checkBombs(char**map, int rows, int columns, Player* players, char* bomb_car);
char** dropBomb(char**map, int v_pos, int h_pos, Player* player, char* bomb_car);
void test(int rows, int columns, Player* players);
