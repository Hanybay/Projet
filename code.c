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

void init_coup(coup cp){
  cp -> degats = 0;
  cp->etata->trdef = 0;
  cp->etata->esquive =0;
  cp->etata->multidmg = 1;
  cp->etata->traterre = 0;
  cp->etate->trdef = 0;
  cp->etate->esquive =0;
  cp->etate->multidmg = 1;
  cp->etate->traterre = 0;
  cp->priorite =0;
  cp->precision = 0;
}

void attaque(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = (p -> force)*p->etat->multidmg;

  /*Priorite*/
  coupperso->priorite = (p -> agilite) + (p -> dexterite)*1/4;

  /*Precision de l'attaque, le minimul sera 10%, il n'y a pas de maximum defini*/
  coupperso -> precision = 90 + p->dexterite - e->agilite;

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
}

void defense (coup coupperso,personnage p, personnage e){ /*p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = 0;

  /*Priorite*/
  coupperso -> priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;

  /*Etats allie*/
  coupperso -> etata -> trdef = 2;
  coupperso -> etata -> esquive = 0;
  coupperso -> etata -> multidmg = 0.66;
  coupperso -> etata -> traterre = 0;

  /* Etats ennemi */
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 1;
  coupperso->etate->traterre = 0;
}



void esquive (coup coupperso personnage p, personnage e){
  /*Degats*/
  coupperso ->  degats = 0;

  /*Priorite*/
  coupperso -> priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1,5;

  /*Etats allie */
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive = 1;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /* Etats ennemi */
  coupperso -> etate -> trdef = 0;
  coupperso -> etate -> esquive = 0;
  coupperso -> etate -> multidmg = 1;
  coupperso -> etate -> traterre = 0;

}

void couppied(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = ((p -> force)/2 + p->dexterite)*1.25*p->etat->multidmg;

  /*priorite*/
  coupperso -> priorite = (p -> agilite) + (p -> dexterite)*1/4;

  /*Precision*/
  coupperso -> precision = 40 + p -> dexterite - e -> agilite;

  /*Etats allie*/
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive =0;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /*Etats ennemis*/
  coupperso -> etate -> trdef = 0;
  coupperso -> etate -> esquive =0;
  coupperso -> etate -> multidmg = 1;
  coupperso -> etate -> traterre = 0;
}



void labourage(coup coupperso, personnage p, personnage e){
  /* Degats */
  coupperso -> degats = (p -> force)*1/2 * p -> etat -> multidmg;

  /* priorite */
  coupperso -> priorite = 0;

  /* Precision */
  coupperso -> precision = 60 + p -> dexterite - e -> agilite;

  /*Etats allie*/
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive = 0;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /*Etats ennemis*/
  coupperso -> etate -> trdef = 0;
  coupperso -> etate -> esquive =0;
  coupperso -> etate -> multidmg = 1;
  coupperso -> etate -> traterre = 1;

}

void decisionia(coup a, personnage ia, personnage perso){
  int decision;
  decision = random(0, 100);
  if (decision<20){
    attaque(a, ia, perso);
  }
  if(decision<40 && decision>=20){
    defense(a, ia, perso);
  }
  if(decision<60 && decision>=40){
    esquive(a, ia, perso);
  }
  if(decision<80 && decision>=60){
    couppied(a, ia, perso);
  }
  if(decision<=100 && decision>=80){
    labourage(a, ia, perso);
  }
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
    if (a->precision <10){
      a->precision = 10;
    }
  }
  if(a -> precision >= precis){
    bb -> vie -= (a -> degats*aa -> etat -> multidmg);
    /*Etat allie*/
    aa->etat->trdef += a->etata->trdef;
    aa->etat->esquive = a->etata->esquive;
    aa->etat->multidmg = aa->etat->multidmg * a->etata->multidmg;
    aa->etat->traterre += a->etata->traterre;
    /*Etats ennemis*/
    bb -> etat -> trdef += a -> etate -> trdef;
    bb -> etat -> esquive = a -> etate -> esquive;
    bb -> etat -> multidmg = aa -> etate -> multidmg * b -> etat -> multidmg;
    bb -> etat -> traterre += a -> etate -> traterre;
  }
  else{
    if(bb -> etat -> esquive == 1 && a -> degats !=0){
      bb -> etat -> esquive = 2;
    }
  }
}

void calcul_attaque_ennemi(coup b, personnage aa, personnage bb){
  int precis;
  precis = random(0,100);
  if (aa -> etat -> esquive == 1){
    b -> precision -= 0.5* aa -> agilite
    if (b -> precision <10){
      b -> precision = 10;
    }
  }
  if(b ->precision>=precis){
    aa -> vie -= (b -> degats*bb -> etat -> multdmg);
    /*Etats allie*/
    bb -> etat -> trdef += b -> etata -> trdef;
    bb -> etat -> esquive = b -> etata -> esquive;
    bb -> etat -> multidmg = bb -> etat -> multidmg * b -> etata -> multidmg;
    bb -> etat -> traterre += b -> etata -> traterre;
    /*Etats ennemis*/
    aa->etat->trdef += b -> etate -> trdef;
    aa->etat->esquive = b -> etate->esquive;
    aa->etat->multidmg = bb -> etat -> multidmg * b -> etate -> multidmg;
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
  if(a->etat->trdef > 5){
    a->etat->trdef =5;
  }
  if(a->etat->trdef > 5){
      a->etat->trdef =5;
  }
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
  if(b -> etat -> esquive == 2){
    b -> etat -> multidmg = b ->etat->multidmg*1.5;
  }
  a -> etat -> esquive = 0;
  b -> etat -> esquive = 0;

  if (a -> etat -> traterre = 1){
    b -> etat -> multidmg = b -> etat -> multidmg*2;
    a -> etat -> traterre = 0;
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

void explications(){
  printf("");
}


void affichage_stats(personnage p){
  printf("Vie / Vie Max : %d, %d", p->vie, p->vitalite);
  printf("Force : %d", p->force);
  printf("Agilite : %d", p->agilite);
  printf("Dexterite : %d", p->dexterite);
}

int main(){
  personnage principal;
  personnage ennemi;
  coup coupperso;
  coup coupenne;
  int go;
  int nbcoup;
  go =0;
  init_personnage(principal);
  init_personnage_prin(principal);
  init_personnage(ennemi);
  init_personnage_enne(ennemi);
  init_coup(coupperso);
  init_coup(coupenne);
  printf("quel est votre nom (20 lettres maximum)?");
  scanf("%s", principal->nom);
  while(nbcoup>4){
    printf("quel sera votre coup?\n");
    printf("0 = attaque, 1 = defense, 2 = esquive\n");
    printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
    printf("6 = Vos stats, 7 = stats ennemi")
    scanf("%d ", nbcoup);
    switch(nbcoup){
      case 0:
        attaque(coupperso, principal, ennemi);
        break;
      case 1:
        defense(coupperso, principal, ennemi);
        break;
      case 2:
        esquive(coupperso, principal, ennemi);
        break;
      case 3:
        couppied(coupperso, principal, ennemi);
        break;
      case 4:
        labourage(coupperso, principal, ennemi);
        break;
      case 5:
        explications();
        break;
      case 6:
        affichage_stats(principal);
        break;
      case 7 :
        affichage_stats(ennemi);
    }

  }
  while(go = 0){

  }
  exit(1);
}
