#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define Valeur_max 255;

typedef struct {
  int trdef;    /*compte le nombre de tour defensif. max 5*/
  int esquive;  /*mode esquive, augmente par 1.5 l'agilite*/
  float multidmg; /*multiplicateur de dégats*/
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
  int priorite; /*Priorite*/
  int precision; /**/
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
  coupperso -> degats = (p -> force)*p->etat->multidmg;
  /*priorite*/

  coupperso->priorite = (p -> dexterite) + (p -> agilite)*1/4;
  coupperso -> precision = 90 + p->dexterite - e->agilite;
  if ((coupperso ->precision) < 33 ){
    coupperso -> precision = 33;
  }
  /*Etats allie*/
  coupperso->etata->trdef = 0;
  coupperso->etata->esquive =0;
  coupperso->etata->multidmg = 1;
  coupperso->etata->traterre = 0;

  /*Etats ennemis*/
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 1;
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

int gameover(int go){
  if (go==1){
    return 1;
  }
  else{
    return 0;
  }
}
void victoire(){
  /*enlever tous les buffs*/
  /*récuperer des hp a hauteur de 15%*/
  /*futur mise en place du menu*/
  printf("victoire!");
  gameover(1);
}
void calcul_attaque_allie(coup a, personnage aa, personnage bb){
  int precis;
  precis = random(0,100);
  if (bb->etat-> esquive == 1){
    a->precision -= 0.5* bb->agilite
    if (a->precision <33){
      a->precision = 33;
    }
  }
  if(a->precision>=precis){
    bb->vie -= (a->degats*aa->etat->multidmg);
    /*Etat allie*/
    aa->etat->trdef += a->etata->trdef;
    aa->etat->esquive = a->etata->esquive;
    aa->etat->multidmg = aa->etat->multidmg * a->etata->multidmg;
    aa->etat->traterre += a->etata->traterre;
    /*Etats ennemis*/
    bb->etat->trdef += a->etate->trdef;
    bb->etat->esquive = a->etate->esquive;
    bb->etat->multidmg = aa->etate->multidmg * b->etat->multidmg;
    bb->etat->traterre += a->etate->traterre;
  }
  else{
    if(bb->etat->esquive ==1 && a->degats !=0){
      bb->etat->esquive = 2;
    }
  }
}

void calcul_attaque_ennemi(coup b, personnage aa, personnage bb){
  int precis;
  precis = random(0,100);
  if (aa->etat-> esquive == 1){
    b->precision -= 0.5* aa->agilite
    if (b->precision <33){
      b->precision = 33;
    }
  }
  if(b->precision>=precis){
    aa->vie -= (b->degats*bb->etat->multdmg);
    /*Etats allie*/
    bb->etat->trdef += b->etata->trdef;
    bb->etat->esquive = b->etata->esquive;
    bb->etat->multidmg = bb->etat->multidmg * b->etata->multidmg;
    bb->etat->traterre += b->etata->traterre;
    /*Etats ennemis*/
    aa->etat->trdef += b->etate->trdef;
    aa->etat->esquive = b->etate->esquive;
    aa->etat->multidmg = bb->etat->multidmg * b->etate->multidmg;
    aa->etat->traterre += b->etate->traterre;
  }

  else{
    if(bb->etat->esquive ==1 && a->degats !=0){
       bb->etat->esquive = 2;
    }
  }
}

void findetour(personnage a, personnage b){
  a->multdmg =1;
  b->multdmg = 1;

  if(a->etat->trdef > 0){
    a->etat->trdef -=1;
    b->etat->multidmg = b->etat->multidmg*0.66;
  }
  if(b->etat->trdef > 0){
    b->etat->trdef -=1;
    a->etat->mutlidmg = a->etat->multidmg*0.66;
  }

  if(a->etat->esquive == 2){
    a->etat->multidmg = a ->etat->multidmg*1.5;
  }
  if(b->etat->esquive == 2){
    b->etat->multidmg = b ->etat->multidmg*1.5;
  }
  a->etat->esquive = 0;
  b->etat->esquive = 0;

  if (a->etat->traterre = 1){
    b->etat->multidmg = b->etat->multidmg*2;
    a->etat->traterre = 0;
  }
  if (b->etat->traterre = 1){
    a->etat->multidmg = a->etat->multidmg*2;
    b->etat->traterre = 0;
  }
}

void calcul_du_tour(coup a, coup b, personnage aa, personnage bb){
  int egalite;
  if(a->priorite > b->priorite){
    calcul_attaque_allie();
    if (bb->vie >0){
      calcul_attaque_ennemi();
    }
  }
  if(a->priorite < b->priorite){
    calcul_attaque_ennemi();
    if (aa->vie >0){
      calcul_attaque_allie();
    }
  }
  if(a->priorite == b->priorite){
    egalite = random(0,100);
    if(egalite > 50){
      calcul_attaque_allie();
      if (bb->vie >0){
        calcul_attaque_ennemi();
      }
    }
    if(egalite <= 50){
      calcul_attaque_ennemi();
      if (aa->vie >0){
        calcul_attaque_allie();
      }
    }
  }
  if (aa->vie <0){
    gameover(1);
  }
  if (bb->vie <0){
    victoire();
  }
  findetour(aa, bb);
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
