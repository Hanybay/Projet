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
  int score;
  int *scoring = &score;
  int *victoire = &vic;
  int soin;
  int *csoigner = &soin;
  int *pts = &points;
  int *nb_combat = &comb;
  points = 20;
  comb = 0;
  vic = 1;
  score = 0;
  p_prin= &principal;
  p_enne= &ennemi;
  principal = init_personnage();
  ennemi = init_personnage();
  init_personnage_prin(p_prin);
  init_personnage_enne(p_enne,nb_combat);
  lancer_jeu(p_prin, p_enne, pts, nb_combat, victoire, csoigner, scoring);
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
  int score;
  int *scoring = &score;
  int *csoigner = &soin;
  int *pts = &points;
  int *nb_combat = &comb;
  int *victoire = &vic;
  points = 0;
  comb = 0;
  vic = 1;
  score =0;
  p_prin= &principal;
  p_enne= &ennemi;
  principal = init_personnage();
  ennemi = init_personnage();
  load_game(pts, nb_combat, p_prin, p_enne, victoire, csoigner, scoring);
  printf("\n\nTEST\n\n");
  if (p_prin->nom[0]!='\0'){
    lancer_jeu(p_prin, p_enne, pts, nb_combat, victoire, csoigner, scoring);
  }
}

void scores(){
  /*Charger et afficher les fichier sauvegarder*/
  int i,j;

  FILE* fichier = NULL;
  fichier = fopen("score.txt","r");
  printf("\n");

  if(fichier==NULL){
    printf("ce slot n'existe pas");
    exit(-1);
  }
  else {
    for(i=0; i < 10;i++){
      if(fscanf(fichier,"%d\n",&j)!=1){
        printf("%d erreur\n",i);
      }
      printf("%d : %d\n",i+1,j);
    }
  }

  fclose(fichier);
}





void lancer_jeu(personnage p_prin, personnage p_enne, int *pts, int *nb_combat, int *vic, int *csoigner, int *score){
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
  coupperso = init_coup();
  coupenne = init_coup();
  while(continu >= 1){
    if (*vic ==1){
      amelioration(pts ,p_prin, asave, vic, csoigner);
    }

    if (*asave != 1){
      while(go == 0 && *vic == 0){
        while((nbcoup>4 || nbcoup<0) && nbcoup != 9){
          nbcoup= -1;
          while (nbcoup >10 || nbcoup<0){
            do {
              printf("\nquel sera votre coup?\n");
              printf("0 = attaque, 1 = defense, 2 = esquive\n");
              printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
              printf("6 = Vos stats, 7 = stats ennemi, 8 = sauvegarde\n");
              printf("9 = sauvegarder et quitter\n");
            }while (scanf("%d", &nbcoup) < 1);
            vider_buffer();
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
              sauvegarde(pts,nb_combat,p_prin,p_enne, vic, csoigner, score);
              break;
            case 9 :
              sauvegarde(pts,nb_combat,p_prin,p_enne, vic, csoigner, score);
              continu =0;
              go=1;
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
          if (p_prin->vie <= 0){
            go = 1;
            save_score(score);
            continu = 0;
          }
          else{
            if (p_enne->vie <= 0){
              *vic = 1;
              *pts += 10;
              *nb_combat+=1;
              *score += 200+((p_prin->vie*100)/p_prin->vitalite);
            }
          }

        }
      }
    }
    else{
      sauvegarde(pts,nb_combat,p_prin,p_enne,vic, csoigner, score);
      continu =0;
    }
    go = 0;
    init_personnage_enne(p_enne,nb_combat);
  }
}
