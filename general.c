#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tour.h"


int main(){
  personnages principal;
  personnage p_prin;
  personnages ennemi;
  personnage p_enne;
  coups coupperso;
  coups coupenne;
  coup coupp;
  coup coupe;
  int go, vic, continu;
  int nbcoup;
  int points;
  int *pts;
  srand(time(NULL));

  go = 0;
  vic = 0;
  continu = 1;
  p_prin= &principal;
  p_enne= &ennemi;
  coupp= &coupperso;
  coupe= &coupenne;
  *pts = &points;
  points = 20;

  principal = init_personnage();
  init_personnage_prin(p_prin);
  ennemi = init_personnage();
  init_personnage_enne(p_enne);
  printf("\nstats personnage \n");
  affichage_stats(p_prin);
  printf("\nstats ennemis \n");
  affichage_stats(p_enne);
  nbcoup = -1;


  while(continu >= 1){
    init_personnage(p_enne);
    init_personnage_enne(p_enne);
    coupperso = init_coup();
    coupenne = init_coup();
    amelioration(*pts ,p_prin);
    printf("je suis passé par là\n\n");
    while(go == 0 && vic == 0){
      while(nbcoup>4 || nbcoup<0){
        nbcoup= -1;
        while (nbcoup >8 || nbcoup<0){
          do {
            printf("\nquel sera votre coup?\n");
            printf("0 = attaque, 1 = defense, 2 = esquive\n");
            printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
            printf("6 = Vos stats, 7 = stats ennemi\n");
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
        }
      }
      nbcoup= -1;
      printf("\n\n\n");
      printf("coup choisis par le joueur : \n");
      affichage_coup(coupp);
      decisionia(coupe, p_enne, p_prin);
      printf("coup choisis par l'ordinateur : \n");
      affichage_coup(coupe);
      printf("calcul du tour\n\n\n");

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
          vic = 1;
          *pts += 5;
          p_prin -> vie = p_prin->vie + 50/100*p_prin->vitalite;
          if (p_prin->vie > p_prin->vitalite){
            p_prin->vie = p_prin->vitalite;
          }
        }
      }
    }
    vic = 0;
    go = 0;
    printf("voulez vous continuez? 0 pour non, 1 pour oui\n");
    vider_buffer();
    while (scanf("%d", &continu) != 1){
      vider_buffer();
      printf("voulez vous continuez? 0 pour non, 1 pour oui\n");
    }
  }
  exit(1);
}
