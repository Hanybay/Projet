#include "personnage.h"

personnages init_personnage(){
  personnages p;
  int i;
  for (i=0; i<19; i++){
    p.nom[i]='\0';
  }
  p.force = 45 + aleat(-10, 10);  /*Les stats sont tiré aléatoirement a chaque nouvelle partie*/
  p.agilite = 45 + aleat(-10, 10);  /*ennemi comme personnage principal*/
  p.dexterite = 45 + aleat(-10, 10);
  p.vitalite = 500 + aleat(-50, 50);
  p.vie = p.vitalite; /*A l'initialisation Pv = Pv max*/
  p.trdef = 0;
  p.esquive = 0;
  p.traterre=0;
  p.multidmg=100;
  return p;
}

void init_personnage_prin(personnage p){
  printf("Le nom de votre personnage en 19 lettres ou moins?  ");
  while(scanf("%s ", p->nom)<1){
    printf("Le nom de votre personnage en 19 lettres ou moins?  ");
    vider_buffer();
  }
     /*Afin de rentrer le prénom, il faudra rentrer*/
}

void init_personnage_enne(personnage p){
  p->nom[0] = 'M';
  p->nom[1] = 'i';
  p->nom[2] = 'c';
  p->nom[3] = 'h';
  p->nom[4] = 'e';
  p->nom[5] = 'l';
}

void affichage_stats(personnage p){
  /*On affichera les stats, on pourra voir aussi ceux des ennemis*/
  printf("%s est le nom du personnage\n", p->nom);
  printf("Vie / Vie Max : %d/%d\n", p->vie, p->vitalite);
  printf("Force : %d\n", p->force);
  printf("Agilite : %d\n", p->agilite);
  printf("Dexterite : %d\n", p->dexterite);
}

void affichage_etats(personnage p){
  printf("%s a les etats suivants :\n", p->nom);
  printf("etat esquive est a %d\n", p->esquive);
  printf("etat a terre est a %d\n", p->traterre);
  printf("Multiplicateur de dégats est à %d", p->multidmg);
  printf("Etat defensif est a %d\n", p->trdef);
}
