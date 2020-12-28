#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define Valeur_max 255;

typedef struct {
  int trdef;    /*compte le nombre de tour defensif. max 5*/
  int esquive;  /*mode esquive, augmente pas mal l'esquive*/
  float multidmg; /*multiplicateur de degats*/
  int traterre; /*compte le nombre de tour a terre*/
} etat;

typedef etat *etats;

typedef struct {
  char nom[20]; /*Nom du personnage*/
  int vitalite; /*Valeur max de pv*/
  int vie; /*PV actuel*/
  int force; /*Valeur offensive*/
  int agilite; /*Taux supplementaire d'esquive*/
  int dexterite; /*Taux supplementaire de precision*/
  etats etat; /*les etats du personnage*/
} personnages;

typedef personnages *personnage;

typedef struct{
  int degats; /*Degats que portera le coup*/
  etats etata; /*Affectation d'etat allie*/
  etats etate; /*Affectation d'etat ennemi*/
  int priorite; /*Vitesse de l'attaque*/
  int precision; /*Precision qu'elle aura*/
}coups;

typedef coups *coup;

int random(int x, int y){
  int alea;
  srand(time(NULL));
  alea = rand()%(y-x+1)+x; /*On aura besoin de cette fonctions pour beaucoup de choses*/
  return alea;
}

void init_personnage(personnage p){
  p->force = 45 + random(-20, 20);  /*Les stats sont tiré aléatoirement a chaque nouvelle partie*/
  p->agilite = 45 + random(-20, 20);  /*ennemi comme personnage principal*/
  p->dexterite = 45 + random(-20, 20);
  p->vitalite = 500 + random(-100, 100);
  p->vie = p->vitalite; /*A l'initialisation Pv = Pv max*/
  p->lesetat->traterre = 0;
  p->lesetat->trdef = 0;
  p->lesetat->esquive = 0;
  p->lesetat->multidmg = 1;
}

void init_personnage_prin(personnage p){
  printf("Le nom de votre personnage en 19 lettres ou moins");
  scanf("%s", p->nom); /*Afin de rentrer le prénom, il faudra rentrer*/
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
  cp -> degats = 0; /*Tout est à 0 pour l'initialisation d'un coup a part le multiplicateur*/
  cp->etata->trdef = 0;
  cp->etata->esquive =0;
  cp->etata->multidmg = 1;
  cp->etata->traterre = 0;
  cp->etate->trdef = 0;
  cp->etate->esquive =0;
  cp->etate->multidmg = 1;
  cp->etate->traterre = 0;
  cp->priorite = 0;
  cp->precision = 0;
}

void attaque(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = (p -> force);
  /*Les dégats sont proportionnel à l'attaque*/

  /*Priorite*/
  coupperso->priorite = (p -> agilite) + (p -> dexterite)*1/4;
  /*La priorité est proportionnel à l'agilité, et un peu a la dexterite*/

  /*Precision de l'attaque, le minimum sera 10%, il n'y a pas de maximum defini*/
  coupperso -> precision = 90 + p->dexterite - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Etats allie*/
  /*Pour une attaque normale, il n'y a aucun buff*/
  coupperso->etata->trdef = 0;
  coupperso->etata->esquive =0;
  coupperso->etata->multidmg = 1;
  coupperso->etata->traterre = 0;

  /*Etats ennemis*/
  /*Pour une attaque normale, il n'y a aucun malus*/
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 1;
  coupperso->etate->traterre = 0;
}

void defense (coup coupperso,personnage p, personnage e){ /*p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = 0;
  /*Lors d'une defense, le personnage n'attaque pas*/

  /*Priorite*/
  coupperso -> priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  /*La priorite est plus élevé qu'une attaque simple*/

  /*Etats allie*/
  /*La défense donne un "buff" de défense sur plusieurs tour*/
  coupperso -> etata -> trdef = 2;
  coupperso -> etata -> esquive = 0;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /* Etats ennemi */
  /*Cela inflige un debuff de dégâts a l'ennemi*/
  coupperso->etate->trdef = 0;
  coupperso->etate->esquive =0;
  coupperso->etate->multidmg = 0.66;
  coupperso->etate->traterre = 0;
}

void esquive (coup coupperso,personnage p, personnage e){
  /*Degats*/
  coupperso ->  degats = 0;
  /*Les dégats d'une esquive sont = à 0*/

  /*Priorite*/
  coupperso -> priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  coupperso -> priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  /*la priortité est plus elevé qu'une attaque, en espérant être plus rapide que l'ennemi*/

  /*Etats allie */
  /*Inflige un buff d'agilité, correspondant a un malus de précision pour l'ennemi*/
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive = 1;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /* Etats ennemi */
  /*il n'y a pas de malus supplementaire pour l'ennemi*/
  coupperso -> etate -> trdef = 0;
  coupperso -> etate -> esquive = 0;
  coupperso -> etate -> multidmg = 1;
  coupperso -> etate -> traterre = 0;
}

void couppied(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = ((p -> force)/2 + p->dexterite)*1.25;
  /*Les dégats sont proportionnel a la dexterite et un peu a la force, les dégats peuvent être puissant*/

  /*priorite*/
  coupperso -> priorite = (p -> agilite) + (p -> dexterite)*1/4;
  /*Priorité normale*/

  /*Precision*/
  coupperso -> precision = 30 + p -> dexterite - e -> agilite;
  /*La priorité de base est basse, mais si la dexterite est bien monte, ce ne sera pas un probleme*/

  /*Etats allie*/
  /*L'attaque, ne donne aucun bonus*/
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive =0;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /*Etats ennemis*/
  /*L'attaque n'inflige aucun Malus*/
  coupperso -> etate -> trdef = 0;
  coupperso -> etate -> esquive =0;
  coupperso -> etate -> multidmg = 1;
  coupperso -> etate -> traterre = 0;
}

void labourage(coup coupperso, personnage p, personnage e){
  /* Degats */
  coupperso -> degats = (p -> force)*1/4;
  /*les dégats sont minimes, mais si ça touche, alors l'avantage est certain*/

  /* priorite */
  coupperso -> priorite = 0;
  /*la priotité est nulle, car prendre l'avantage a un prix*/

  /* Precision */
  coupperso -> precision = 50 + p -> dexterite - e -> agilite;
  /*La précision est moyenne, et sera aussi en fonction des pvs*/

  /*Etats allie*/
  coupperso -> etata -> trdef = 0;
  coupperso -> etata -> esquive = 0;
  coupperso -> etata -> multidmg = 1;
  coupperso -> etata -> traterre = 0;

  /*Etats ennemis*/
  /*inflige un malus, si c'est le cas, les dégats seront multiplié au prochain tours*/
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

void calcul_attaque(coup a, personnage aa, personnage bb){
  int precis;
  precis = random(0,100);
  /*La precision est calculé en lancant 1d100. Bien qu'on peut largement dépassé*/
  if (bb->etat-> esquive == 1){
    a->precision -= 0.5* bb->agilite;
    /*le debuff de précision par l'esquive  est ici*/
    if (a->precision <10){
      a->precision = 10;
    /*La précision ne pas être plus bas que "10%""*/
    }
  }
  if(a -> precision >= precis){
    /*Si l'attaque réussi, alors tout est appliqué*/
    bb -> vie -= (a -> degats*aa->etat->multidmg);
    /*Etat allie*/
    aa->etat->trdef += a->etata->trdef;
    aa->etat->esquive = a->etata->esquive;
    aa->etat->multidmg = aa->etat->multidmg * a->etata->multidmg;
    aa->etat->traterre += a->etata->traterre;
    /*Etats ennemis*/
    bb -> etat -> trdef += a -> etate -> trdef;
    bb -> etat -> esquive = a -> etate -> esquive;
    bb -> etat -> multidmg = aa -> etate -> multidmg * bb -> etat -> multidmg;
    bb -> etat -> traterre += a -> etate -> traterre;
  }
  else{
    /*Si l'attaque ne réussi pas, et que l'esquive à réussi*/
    if(bb -> etat -> esquive == 1 && a -> degats !=0){
      bb -> etat -> esquive = 2;
      /*alors on passe l'etat esquive a 2*/
    }
  }
}

void findetour(personnage a, personnage b){
  /*Retour à 1 de la mutiplication pour le calculer au prochain tour*/
  a->multdmg =1;
  b->multdmg = 1;

  if(a->etat->trdef > 5){
    a->etat->trdef =5;
    /*On vérifie si les tours de défense ne dépasse pas la limite autorisé*/
  }
  if(b->etat->trdef > 5){
      b->etat->trdef =5;
  }
  if(a->etat->trdef > 0){
    a->etat->trdef -=1;
    b->etat->multidmg = b->etat->multidmg*0.66;
    /*On applique l'état, baissant */
  }
  if(b->etat->trdef > 0){
    b->etat->trdef -=1;
    a->etat->multidmg = a->etat->multidmg*0.66;
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
    calcul_attaque(a, aa, bb);
    if (bb->vie >0){
      calcul_attaque(b, bb, aa);
    }
  }
  if(a->priorite < b->priorite){
    calcul_attaque(b , bb, aa);
    if (aa->vie >0){
      calcul_attaque(a, aa, bb);
    }
  }
  if(a->priorite == b->priorite){
    egalite = random(0,100);
    if(egalite > 50){
      calcul_attaque(a, aa, bb);
      if (bb->vie >0){
        calcul_attaque(b, bb, aa);
      }
    }
    if(egalite <= 50){
      calcul_attaque(b, bb, aa);
      if (aa->vie >0){
        calcul_attaque(a, aa, bb);
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

void explication(){
  printf("Pour jouer à notre fabuleux jeux, vous disposez d'une action parmis 5 chaque tour.\n");
  printf("Attaque : attaque normal, les dégats sont sur la force brut,précision elevée, pas de changement d'état.\n");
  printf("Défense : défense cotre un coup, vous suibissez pour les 2 prochains tours 66 pour cent des dégats normaux, stackable sur 5 tours.\n");
  printf("Esquive : esquive d'un coup. Reduction des dégats à 100%.\n");
  printf("Labourage : Une chance de mettre a terre l'adversaire au prix d'attaquer en dernier.\n");
  printf("Coup de pied : attaque infligeant de lourds dégats au prix d'une précision moyenne.\n");

}

void affichage_stats(personnage p){
  printf("Vie / Vie Max : %d, %d\n", p->vie, p->vitalite);
  printf("Force : %d\n", p->force);
  printf("Agilite : %d\n", p->agilite);
  printf("Dexterite : %d\n", p->dexterite);
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
  printf("quel est votre nom (20 lettres maximum)?  ");
  scanf("%s ", principal->nom);
  while(nbcoup>5){
    printf("quel sera votre coup?\n");
    printf("0 = attaque, 1 = defense, 2 = esquive\n");
    printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
    printf("6 = Vos stats, 7 = stats ennemi\n");
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
        explication();
        break;
      case 6:
        affichage_stats(principal);
        break;
      case 7 :
        affichage_stats(ennemi);
        break;
    }
  }
  decisionia(coupenne, ennemi, principal);
  calcul_du_tour(coupperso, coupenne, principal, ennemi);
  affichage_stats(principal);
  affichage_stats(ennemi);
  while(go == 0){
  }
  exit(1);
}
