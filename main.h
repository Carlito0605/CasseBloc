typedef struct player{
    int hp;
    int max_hp;
    int current_bombs;
    int max_bombs;
    int range;
    int bomb_special_power_up; //-1=rien, 0=Passe bomb, 1=Bomb kick
    int invicibility; //tours restants d'invincibilité
    int heart; //-1=coeur déjà utilisé, 0=pas de coeur, 1=a un coeur
}Player;