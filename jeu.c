#include "jeu.h"


void menu_principal(){
  int choix;
  choix = -1;
  do{
    choix = -1;
    do {
      printf("\n\n");
      printf("Bienvenue dans le jeu MKF FIGHTER!!\n\n");
      printf("      0:Nouvelle partie\n");
      printf("      1:Charger partie\n");
      printf("         2:Scores\n");
      printf("         3:Quitter\n");
    }while (scanf("%d", &choix) < 1 && (choix <0 || choix>4));
    vider_buffer();
    switch(choix){
      case 0:
        nouvelle_partie();
        break;
      case 1:
        charger_partie();
        break;
      case 2:
        scores();
        break;
      case 3:
        break;
    }
  }while(choix !=3);
}

void nouvelle_partie(){
  personnages principal;
  personnage p_prin;
  personnages ennemi;
  personnage p_enne;
  int points;
  int comb;
  int vic;
  int *victoire = &vic;
  int soin;
  int *csoigner = &soin;
  int *pts = &points;
  int *nb_combat = &comb;
  points = 20;
  comb = 0;
  vic = 1;
  p_prin= &principal;
  p_enne= &ennemi;
  principal = init_personnage();
  ennemi = init_personnage();
  init_personnage_prin(p_prin);
  init_personnage_enne(p_enne,nb_combat);
  lancer_jeu(p_prin, p_enne, pts, nb_combat, victoire, csoigner);
}

void charger_partie(){
  personnages principal;
  personnage p_prin;
  personnages ennemi;
  personnage p_enne;
  int points;
  int comb;
  int soin;
  int vic;
  int *csoigner = &soin;
  int *pts = &points;
  int *nb_combat = &comb;
  int *victoire = &vic;
  pts = 0;
  comb = 0;
  vic = 1;
  p_prin= &principal;
  p_enne= &ennemi;
  principal = init_personnage();
  ennemi = init_personnage();
  load_game(pts, nb_combat, p_prin, p_enne, victoire, csoigner);
  printf("\n\nTEST\n\n");
  if (p_prin->nom[0]!='\0'){
    lancer_jeu(p_prin, p_enne, pts, nb_combat, victoire, csoigner);
  }
}

void scores(){
  /*Charger et afficher les fichier sauvegarder*/
}



void lancer_jeu(personnage p_prin, personnage p_enne, int *pts, int *nb_combat, int *vic, int *csoigner){
  int go, continu, nbcoup, save;
  coups coupperso;
  coups coupenne;
  coup coupp;
  coup coupe;
  int *asave = &save;
  coupp=&coupperso;
  coupe=&coupenne;
  continu = 1;
  save=0;
  while(continu >= 1){
    coupperso = init_coup();
    coupenne = init_coup();
    if (*vic ==1){
      amelioration(pts ,p_prin, asave, vic, csoigner);
    }
    *vic = 0;
    if (*asave != 1){
      while(go == 0 && *vic == 0){
        while(nbcoup>4 || nbcoup<0){
          nbcoup= -1;
          while (nbcoup >10 || nbcoup<0){
            do {
              printf("\nquel sera votre coup?\n");
              printf("0 = attaque, 1 = defense, 2 = esquive\n");
              printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
              printf("6 = Vos stats, 7 = stats ennemi, 8 = sauvegarde\n");
              printf("9 = sauvegarder et quitter\n");
              vider_buffer();
            }while (scanf("%d", &nbcoup) < 1);
          }
          switch(nbcoup){
            case 0:
              attaque(coupp, p_prin, p_enne);
              break;
            case 1:
              defense(coupp, p_prin, p_enne);
              break;
            case 2:
              esquive(coupp, p_prin, p_enne);
              break;
            case 3:
              couppied(coupp, p_prin, p_enne);
              break;
            case 4:
              labourage(coupp, p_prin, p_enne);
              break;
            case 5:
              explication();
              break;
            case 6:
              affichage_stats(p_prin);
              break;
            case 7 :
              affichage_stats(p_enne);
              break;
            case 8 :
              sauvegarde(pts,nb_combat,p_prin,p_enne, vic, csoigner);
              break;
            case 9 :
              sauvegarde(pts,nb_combat,p_prin,p_enne, vic, csoigner);
              continu =0;
              break;
          }
        }
        nbcoup= -1;
        if (continu >= 1){
          printf("\n\n\n");
          printf("coup choisis par le joueur : \n");
          affichage_coup(coupp);
          decisionia(coupe, p_enne, p_prin);
          printf("coup choisis par l'ordinateur : \n");
          affichage_coup(coupe);
          printf("\n\ncalcul du tour\n");

          calcul_du_tour(coupp, coupe, p_prin, p_enne);
          printf("Affichage des stats du personnage principal\n");
          affichage_stats(p_prin);
          printf("Affichage des stats de l'ennemi\n");
          affichage_stats(p_enne);
          if (p_prin->vie <= 0){
            go = 1;
          }
          else{
            if (p_enne->vie <= 0){
              *vic = 1;
              *pts += 10;
              *nb_combat+=1;
            }
          }
        }

        printf("voulez vous continuer? 0 pour non, 1 pour oui\n");
        while (scanf("%d", &continu) != 1){
          vider_buffer();
          printf("voulez vous continuez? 0 pour non, 1 pour oui\n");
        }
      }
    }
    else{
      sauvegarde(pts,nb_combat,p_prin,p_enne,vic, csoigner);
      continu =0;
    }
    *vic = 0;
    go = 0;
    init_personnage_enne(p_enne,nb_combat);
  }
}
