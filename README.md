*Auteurs Ronan KIELT et Charles CRETOIS*

#Sommaire :
1. Présentation du projet
2. Ce qui a été fait 
3. Ce qui n'a pas été fait
4. Notice d'utilisation
   1. Lancer le jeu
   2. Actions possibles
   3. Bombes
   4. Objets
   5. Conditions de victoire

### 1. Présentation du projet :

   Le but de ce projet est de créer un jeu multijoueur qui n'est pas du tout un plagiat de bomberman.
   
   Ce projet doit être coder en C et est un travaille de groupe.
   
   Il a été réalisé en 1 mois et a été partagé aux collaborateurs via GIT en Gitflow.

   Ce projet avait pour but de synthétiser tout ce qui a été apris durant la piscine de C de l'ESGI de 3ème année.

   Les évaluateurs sont Nathanael Demacon et Mickaël Saint-Martin.

   Lien du Git : https://github.com/Carlito0605/CasseBloc

### 2. Ce qui a été fait :

* Positionnement d'une bombe (à côté du joueur)
* Explosion d'une bombe
* Explosion bloquée par un mur
* Explosion d'un joueur avec un bombe
* Explosion d'un mur destructible avec une bombe
* Explosions passent à travers les trous
* Propagation de bombes
* Récupérations d'objets
* Gestion de la mort d'un joueur
* Effets de tout les objets
* BombKick
* PasseBomb -> (saut derrière la bombe si possible)
* Gestion des tours
* Plusieurs actions pour un joueur par tour
* Menu Démarrer
* Gestion du fichier de cartes
* Affichage clean d'une map
* Initialisation d'une partie via le menu
* Mouvement des joueurs
* Collisions
* Trou dans la carte (pour le joueur et bombKick)
* Gestion des touches pressés

### 3. Ce qui n'a pas été fait :

* Positionnement d'une bombe à l'emplacement du joueur
* Démarrer le serveur
* Rejoindre un serveur
* Serveur Multijoueur
* Jeu en temps réel (BONUS)
* SDL (BONUS)

### 4. Notice d'utilisation :

1. Lancer le jeu :

![](.\Captures d'écrans\Menu.PNG "Menu")

      Vous pouvez lancer le jeu en double cliquant sur CasseBloc.exe !

      Quand vous lancez le jeu appuyez sur les flèches directionnelles pour choisir une option. 
      (Actuellement il n'y a pas de jeu en réseau donc vous ne pouvez choisir que "Solo")
      Appuyer sur 'entrée' quand vous avez choisi !
    
      Ensuite vous pouvez choisir le nombre de joueur de la partie (entre 2 et 4 compris)
      Vous avez ensuite une séléction de cartes, vous pouvez décocher
      les cartes sur lequelles vous ne voulez pas joueur en appuyant sur 'entrée'. 
    
      Une fois prêts vous pouvez commencer en appuyant sur 'entrée' sur l'option 'commencer la partie' !

2. Actions possibles :
      

![](.\CasseBloc\Captures d'écrans\Debut du jeu.PNG)

      Une fois que la partie commencé voici le déroulement du jeu :

      - Tour du premier joueur il appuye sur 'entrée' quand il est prêt, 
      ou quitter en appuyant sur 'echap'
      - Chaque joueur commence avec 1 point de vie et une portée d'explosion de bombes de 2
      - Il peut faire 3 actions
      - Puis son tour se termine et c'est au tour du prochain joueur et ainsi de suite...

      Les joueurs sont représentés par ces symboles :
      ♠ -> Joueur 1
      ♥ -> Joueur 2
      ♣ -> Joueur 3
      ♦ -> Joueur 4

      Voici les actions que chaque joueur peut faire :

      - Il peut avancer en appuyant sur les flèches directionnelles, 
      il ne peut pas avancer à un endroit qui est déjà bloqué par un mur (ou un mur destructible), 
      un autre joueur ou une bombe (sauf s'il possède 'Passe-Bombe'). 
      
      Si le joueur sort de la carte il est replacé au côté opposé de la carte.
      
      Si le joueur marche sur un objet ('#') il le récupère.

      - Il peut poser des bombes dans la direction choisi si l'espace est libre :
         * Appuyer sur 1 pour poser une bombe à droite
         * Appuyer sur 2 pour poser une bombe à gauche
         * Appuyer sur 3 pour poser une bombe en haut
         * Appuyer sur 4 pour poser une bombe en bas

      

      - Si le joueur possède l'amélioration 'bombKick',
      il peut pousser une bombe jusqu'à ce qu'elle rencontre un obstacle en appuyant sur ces touches :
         * Appuyer sur 5 pour pousser une bombe à droite
         * Appuyer sur 6 pour pousser une bombe à gauche
         * Appuyer sur 7 pour pousser une bombe en haut
         * Appuyer sur 8 pour pousser une bombe en bas

      - Il peut quitter la partie en appuyant sur 'echap'


![](.\CLionProjects\CasseBloc\Captures d'écrans\Actions.PNG)


3. Bombes :


      Chaque joueur dispose d'un nombre de bombes limités définis dans la séléctions de la carte.
      Quand un joueur n'a plus de bombes il ne peut plus en poser.
      Mais il récupère sa bombe une fois qu'elle a explosée !

      Les bombes explosent au bout de 3 tours et leur état est représenté par les symboles suivants :
      O -> La bombe explose dans 3 tours  
      ¤ -> La bombe explose dans 2 tours  
      @ -> La bombe explose au prochain tour

      Quand une bombe explose elle montre son rayon d'explosion avec les caractères '*'.
      Ces carractères disparaissent une fois que les tours reprennent.

      Quand une explosion touche un joueur elle lui inflige 1 dégat !
      
      Quand une v touche un mur, l'explosion d'arrête de se côter,
      donc un joueur peut se cacher derrière un mur par exemple.

      Quand une explosion touche un mur destructible elle le casse,
      le mur a ensuite une chance sur 6 de faire tomber un objet.

      Quand une explosion touche un objet, l'objet est détruit.

      Quand une explosion touche une autre bombe, elle l'a fait exploser également et ainsi de suite.


![](.\CLionProjects\CasseBloc\Captures d'écrans\Explosion d'une bombe.PNG)


4. Objets :



      Quand vous récupérez un objet vous avez une chance différente d'obtenir chaque objet :
      
      Bomb Up : Augmente de 1 le nombre de bombes du joueur.                                          -> 20% de chance de l'obtenir
      Bomb Down : Diminue de 1 le nombre de bombes du joueur.                                         -> 20% de chance de l'obtenir

      Flamme Jaune : Augmente de 1 la portée des bombes du joueur.                                    -> 20% de chance de l'obtenir
      Flamme Bleue : Diminue de 1 la portée des bombes du joueur.                                     -> 20% de chance de l'obtenir
      Flamme Rouge : Met la portée des bombes du joueur au maximum. Cet objet est très                -> 2% de chance de l'obtenir
      rare.

      Passe-Bombes : Permet de traverser les bombes. Remplace Bomb Kick quand obtenu.                 -> 5% de chance de l'obtenir
      Bomb Kick : Permet d’envoyer les bombes comme un ballon de football, dans la direction          -> 5% de chance de l'obtenir
      opposée au joueur jusqu’à tomber sur un mur (destructible ou non). Remplace Passe-Bombes
      quand obtenu.

      Invincibilité : Bonus temporaire (2 tours) permettant au joueur de                              -> 2% de chance de l'obtenir
      résister aux explosions le temps du bonus.

      Cœur : Permet au joueur de survivre à une explosion. Ne peut pas être cumulé. Une fois le       -> 3% de chance de l'obtenir
      cœur utilisé, il sera impossible d’en récupérer un autre durant le reste de la partie.
      
      Vie : Augmente de 1 le nombre de points de vie du joueur.                                       -> 2% de chance de l'obtenir


![](.\CLionProjects\CasseBloc\Captures d'écrans\Récupération d'objets.PNG)


5.Conditions de victoire :



      Quand un joueur n'a plus de point de vie il est élminé et ne peut plus jouer pour cette partie.

      Une partie se termine quand il reste 1 ou 0 joueurs encore en vie :

         - Le dernier joueur en vie gagne la partie !
         - Si les deux derniers joueurs sont éliminés en même temps par une bombe celà provoque alors une égalité !

      Vous pouvez ensuite relancé une partie sur les maps précdemment séléctionnées en appuyant sur n'importe quelle touche.
      Ou appuyer sur echap ou '0' pour quitter.
