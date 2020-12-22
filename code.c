#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define Valeur_max 255;

typedef struct {
  int trdef;    /*compte le nombre de tour defensif. max 5*/
  int esquive;  /*mode esquive, augmente par 1.5 l'agilite*/
  int multidmg; /*multiplicateur de dégats*/
  int traterre; /*compte le nombre de tour a terre*/
} etat;

typedef etat *etats;

typedef struct {
  int vie; /*PV actuel*/
  int force; /*Valeur offensive*/
  int vitalite; /*Valeur max de pv*/
  int agilite; /*taux supplementaire d'esquive*/
  int dexterite; /*Taux supplementaire de precision*/
  char nom[20]; /*nom du personnage*/
  etats etat; /*etat*/
} personnages;

typedef personnages *personnage;

typedef struct{
  int degats;
  etats etata; /*Etat allié*/
  etats etate; /*Etat ennemi*/
  int priorite;
  int precision;
}coups;

typedef coups *coup;

int random(int x, int y){
  int alea;
  srand(time(NULL));
  alea = rand()%(y-x+1)+x;
  return alea;
}


void init_personnage(personnage p){
  p->force = 45 + random(-20, 20);
  p->agilite = 45 + random(-20, 20);
  p->dexterite = 45 + random(-20, 20);
  p->vitalite = 500 + random(-100, 100);
  p->vie = p->vitalite;
  p->lesetat->trdef = 0;
  p->lesetat->esquive =0;
  p->lesetat->multidmg = 1;
  p->lesetat->traterre = 0;
}

void init_personnage_prin(personnage p){
  printf("Le nom de votre personnage en 19 lettres ou moins");
  scanf("%s", p->nom);
}


void init_personnage_enne(personnage p){

  p->nom[0] = 'M';
  p->nom[1] = 'i';
  p->nom[2] = 'c';
  p->nom[3] = 'h';
  p->nom[4] = 'e';
  p->nom[5] = 'l';
}

coup attaque(personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  coup coupperso;
  /*Degats*/
  coupperso -> degats = (p -> force) * (p->etat->multidmg);
  /*priorite*/
  
  coupperso->priorite = (p -> dexterite) + (p -> agilite)*1/4;
  coupperso -> precision = 90 + p->dexterite - e->agilite;
  if ((coupperso ->precision) < 33 ){
    coupperso -> precision = 33;
  }
  /*Etats allie*/
  coupperso->etata->trdef = 0;
  coupperso->etata->esquive =0;
  coupperso->etata->multidmg = 0;
  coupperso->etata->traterre = 0;
  /*Etats ennemis*/
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 0;
  coupperso->etate->traterre = 0;

  return coupperso; /*coup inflige a l'ennemi*/
}

coup defense (personnage p, personnage e){ /*p = Attaquant, e = Attaqué*/
  coup coupperso;
  
  /*Degats*/

  coupperso -> etate -> multidmg = coupperso -> etate -> multidmg *0.66;
  
  /*priorite*/
  coupperso -> priorite = ((p -> agilite ) + (p -> dexterite )*1/4)*1/2;
  
  /*Etats allie*/
  coupperso -> etata -> trdef = 2;
  coupperso -> etata -> esquive = 0;
  coupperso -> etata -> multidmg = 0,66 ;
  coupperso -> etata -> traterre = 0;
  
  /* Etats ennemi */
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 0;
  coupperso->etate->traterre = 0;
  
  
  return coupperso; /*coup inflige a l'ennemi*/
}



coup esquive (personnage p, personnage e){
  /*degats*/
  
  /*priorite*/
  
  /*changement d'etat*/
}

void calcul_du_tour(coup a, coup b, personnage aa, personnage bb){
  int egalite;
  if(a->priorite > b->priorite){
    aa->etat = a->etata;
    bb->etat = b->etate;
    bb->vie -= a->degats;
    if (bb->vie > 0){
      aa->vie -= b->degats;
    }
  }
  if(a->priorite < b->priorite){
    bb->etat = b->etata;
    aa->etat = a->etate;
    aa->vie -= b->degats;
    if (aa->vie > 0){
      bb->vie -= a->degats;
    }
  }
  if(a->priorite == b->priorite){
    egalite = random(0,100);
    if(egalite >50){
      aa->etat = a->etata;
      bb->etat = b->etate;
      bb->vie -= a->degats;
      if (bb->vie > 0){
        aa->vie -= b->degats;
      }
    }
    if(egalite <=50){
      bb->etat = b->etata;
      aa->etat = a->etate;
      aa->vie -= b->degats;
      if (aa->vie > 0){
        bb->vie -= a->degats;
      }
    }
  }
}


int main(){
  personnage principal;
  personnage ennemi;
  init_personnage(principal);
  init_personnage_prin(principal);
  init_personnage(ennemi);
  init_personnage_enne(ennemi);

  exit(1);
}
