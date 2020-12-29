#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define Valeur_max 255;

typedef struct {
  int trdef;    /*compte le nombre de tour defensif. max 5*/
  int esquive;  /*mode esquive, augmente pas mal l'esquive*/
  int multidmg; /*multiplicateur de degats*/
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
  int trdef; /*les etats du personnage*/
  int esquive;
  int multidmg;
  int traterre;
} personnages;

typedef personnages *personnage;

typedef struct{
  int degats; /*Degats que portera le coup*/
  int priorite; /*Vitesse de l'attaque*/
  int precision; /*Precision qu'elle aura*/
  int pe_trdef; /*les etats du personnage*/
  int pe_esquive;
  int pe_multidmg;
  int pe_traterre; /*Affectation d'etat allie*/
  int en_trdef; /*les etats du personnage*/
  int en_esquive;
  int en_multidmg;
  int en_traterre; /*Affectation d'etat ennemi*/
}coups;

typedef coups *coup;

int aleat(int x, int y){
  int alea;

  alea = rand()%(y-x+1)+x; /*On aura besoin de cette fonctions pour beaucoup de choses*/
  return alea;
}

/*etat init_etat(){
  etat initial;
  initial.trdef=0;
  initial.esquive=0;
  initial.multidmg=1.0;
  initial.traterre=0;
  return initial;
}*/

personnages init_personnage(){
  personnages p;
  int i;
  for (i=0; i<19; i++){
    p.nom[i]='\0';
  }
  srand(time(NULL));
  p.force = 45 + aleat(-10, 10);  /*Les stats sont tiré aléatoirement a chaque nouvelle partie*/
  p.agilite = 45 + aleat(-10, 10);  /*ennemi comme personnage principal*/
  p.dexterite = 45 + aleat(-10, 10);
  p.vitalite = 500 + aleat(-50, 50);
  p.vie = p.vitalite; /*A l'initialisation Pv = Pv max*/
  p.trdef = 0;
  p.esquive = 0;
  p.traterre=0;
  p.multidmg=0;
  return p;
}



void init_personnage_prin(personnage p){
  printf("Le nom de votre personnage en 19 lettres ou moins?  ");
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

coups init_coup(){
  coups cp;
  cp.degats = 0; /*Tout est à 0 pour l'initialisation d'un coup a part le multiplicateur*/
  cp.pe_trdef = 0;
  cp.pe_esquive =0;
  cp.pe_multidmg = 1;
  cp.pe_traterre = 0;
  cp.en_trdef = 0;
  cp.en_esquive =0;
  cp.en_multidmg = 1;
  cp.en_traterre = 0;
  cp.priorite = 0;
  cp.precision = 0;
  return cp;
}

void attaque(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = (p -> force);
  /*Les dégats sont proportionnel à l'attaque*/

  /*Priorite*/
  coupperso -> priorite = (p -> agilite) + (p -> dexterite)*1/4;
  /*La priorité est proportionnel à l'agilité, et un peu a la dexterite*/

  /*Precision de l'attaque, le minimum sera 10%, il n'y a pas de maximum defini*/
  coupperso -> precision = 90 + p->dexterite - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Etats allie*/
  /*Pour une attaque normale, il n'y a aucun buff*/
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive =0;
  coupperso -> pe_multidmg = 1;
  coupperso -> pe_traterre = 0;

  /*Etats ennemis*/
  /*Pour une attaque normale, il n'y a aucun malus*/
  coupperso->en_trdef = 0;
  coupperso->en_esquive =0;
  coupperso->en_multidmg = 1;
  coupperso->en_traterre = 0;
}

void defense (coup coupperso,personnage p, personnage e){ /*p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso->degats = 0;
  /*Lors d'une defense, le personnage n'attaque pas*/

  /*Priorite*/
  coupperso->priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  /*La priorite est plus élevé qu'une attaque simple*/

  /*Precision de l'attaque, le minimum sera 10%, il n'y a pas de maximum defini*/
  coupperso->precision = 100 + p->dexterite - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Afin d'appliqué l'état, on vérifie d'abord si l'état est déjà actif*/
  /* Etats ennemi */
  /*Cela inflige un debuff de dégâts a l'ennemi*/
  coupperso->en_trdef = 0;
  coupperso->en_esquive =0;
  if (p->trdef<1){
    coupperso->en_multidmg = 0.66;
  }
  else{
    coupperso->en_multidmg = 1;
  }
  coupperso->en_traterre = 0;

  /*Etats allie*/
  /*La défense donne un "buff" de défense sur plusieurs tour*/
  coupperso->pe_trdef = 2;
  coupperso->pe_esquive = 0;
  coupperso->pe_multidmg = 1;
  coupperso->pe_traterre = 0;


}

void esquive (coup coupperso,personnage p, personnage e){
  /*Degats*/
  coupperso->degats = 0;
  /*Les dégats d'une esquive sont = à 0*/

  /*Priorite*/
  coupperso->priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  /*la priortité est plus elevé qu'une attaque, en espérant être plus rapide que l'ennemi*/

  /*Precision de l'attaque, le minimum sera 10%, il n'y a pas de maximum defini*/
  coupperso->precision = 50 + p->dexterite - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Etats allie */
  /*Inflige un buff d'agilité, correspondant a un malus de précision pour l'ennemi*/
  coupperso->pe_trdef = 0;
  coupperso->pe_esquive = 1;
  coupperso->pe_multidmg = 1;
  coupperso->pe_traterre = 0;

  /* Etats ennemi */
  /*il n'y a pas de malus supplementaire pour l'ennemi*/
  coupperso->en_trdef = 0;
  coupperso->en_esquive = 0;
  coupperso->en_multidmg = 1;
  coupperso->en_traterre = 0;
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
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive =0;
  coupperso -> pe_multidmg = 1;
  coupperso -> pe_traterre = 0;

  /*Etats ennemis*/
  /*L'attaque n'inflige aucun Malus*/
  coupperso -> en_trdef = 0;
  coupperso -> en_esquive =0;
  coupperso -> en_multidmg = 1;
  coupperso -> en_traterre = 0;
}

void labourage(coup coupperso, personnage p, personnage e){
  /* Degats */
  coupperso -> degats = (p -> force)*1/4;
  /*les dégats sont minimes, mais si ça touche, alors l'avantage est certain*/

  /* priorite */
  coupperso -> priorite = 0;
  /*la priotité est nulle, car prendre l'avantage a un prix*/

  /* Precision */
  coupperso -> precision = 40 + p -> dexterite - e -> agilite;
  /*La précision est moyenne, et sera aussi en fonction des pvs*/

  /*Etats allie*/
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive = 0;
  coupperso -> pe_multidmg = 1;
  coupperso -> pe_traterre = 0;

  /*Etats ennemis*/
  /*inflige un malus, si c'est le cas, les dégats seront multiplié au prochain tours*/
  coupperso -> en_trdef = 0;
  coupperso -> en_esquive =0;
  coupperso -> en_multidmg = 1;
  coupperso -> en_traterre = 2;

}

void decisionia(coup a, personnage ia, personnage perso){
  int decision;
  decision = aleat(0, 100);
  if (decision<=100){
    attaque(a, ia, perso);
  }
  /*if(decision<40 && decision>=20){
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
  }*/
}


void calcul_attaque(coup a, personnage aa, personnage bb){
  int precis, dmg;
  precis = aleat(0,100);
  /*La precision est calculé en lancant 1d100. Bien qu'on peut largement dépassé*/
  if (bb->esquive == 1){
    a->precision -= 0.5* bb->agilite;
    printf("%s est dans l'état esquive! \n", bb->nom);
    /*le debuff de précision par l'esquive  est ici*/
    if (a->precision <10){
      a->precision = 10;
    /*La précision ne pas être plus bas que "10%""*/
    }
  }
  if(a -> precision >= precis){
    /*Si l'attaque réussi, alors tout est appliqué*/
    dmg = a -> degats*aa->multidmg;
    bb -> vie -= dmg;
    if(dmg>0){
      printf("%s a perdu %d pvs!\n", bb->nom, dmg);
    }
    /*Etat allie*/
    aa->trdef += a->pe_trdef;
    if(a->pe_trdef>0){
      printf("%s se défend, les dégats sont réduit pendant 2 tours!", aa->nom);
    }
    aa->esquive = a->pe_esquive;
    if(a->pe_esquive>0){
      printf("%s se met en posture d'esquive!", aa->nom);
    }
    aa->multidmg = aa->multidmg * a->en_multidmg;
    aa->traterre += a->en_traterre;
    /*Etats ennemis*/
    bb -> trdef += a -> en_trdef;
    bb -> esquive += a -> en_esquive;
    bb -> multidmg = bb -> multidmg * a ->en_multidmg;

    if(bb->traterre !=0){
      bb -> traterre += a -> en_traterre;
      if (a->en_traterre >0){
        printf("%s est en position de faiblesse pendant 2 tours! Profitez en!", bb->nom);
      }
    }
  }
  else{
    /*Si l'attaque ne réussi pas, et que l'esquive à réussi*/
    if(bb -> esquive == 1 && a -> degats !=0){
      printf("%s a esquivé l'attaque de %s ! Il passe en contre-attaque!", bb->nom, aa->nom);
      bb -> esquive = 2;
      /*alors on passe l'etat esquive a 2*/
    }
    else{
      printf("%s a raté son mouvement! \n", aa->nom);
    }
  }
}

void findetour(personnage a, personnage b){
  /*Retour à 1 de la mutiplication pour le calculer au prochain tour*/
  a->multidmg =1.0;
  b->multidmg = 1.0;

  /*On vérifie si les tours de défense ne dépasse pas la limite autorisé*/
  if(a->trdef > 5){
    a->trdef =5;
  }
  if(b->trdef > 5){
      b->trdef =5;
  }

  /*On applique l'état, baissant le multiplicateur ennemi*/
  if(a->trdef > 1){
    b->multidmg = b->multidmg*0.66;
  }
  if(b->trdef > 1){
    a->multidmg = a->multidmg*0.66;
  }
  /*Puis on baise de 1 le nombre de tour de défense*/
  a->trdef -=1;
  b->trdef -=1;

  /*On regarde l'état esquive, si il a fonctionner on applique l'effet*/
  if(a->esquive == 2){
    a->multidmg = a->multidmg*1.5;
  }
  if(b -> esquive == 2){
    b -> multidmg = b ->multidmg*1.5;
  }
  /*Puis quoiqu'il arrive, on enlève l'état esquive*/
  a -> esquive = 0;
  b -> esquive = 0;

  /*Si on a recu l'état a terre alors on multiplie par 2 les dégats qu'on recevra*/
  if (a -> traterre > 0){
    b -> multidmg = b -> multidmg*2;
    a -> traterre -= 1;
  }
  if (b->traterre > 0){
    a->multidmg = a->multidmg*2;
    b->traterre -= 1;
  }
}

void calcul_du_tour(coup a, coup b, personnage aa, personnage bb){
  int egalite;
  /*On verifie la priorite de chaque coup, le plus elevé sera celui qui attaquera en premier*/
  if(a->priorite > b->priorite){
    calcul_attaque(a, aa, bb);
    /*Dans le cas où l'adversaire n'a pas de pv, évidemment on ne calculera pas ses dégâts*/
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
  /*Si les priorité sont égaux, alors on laissera la chance décider*/
  if(a->priorite == b->priorite){
    egalite = aleat(0,100);
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
  /*On applique la fin de tour*/
  findetour(aa, bb);
}

void explication(){
  printf("Pour jouer à notre fabuleux jeux, vous disposez d'une action parmis 5 chaque tour.\n");
  printf("Attaque : attaque normal, les dégats sont sur la force brut,précision elevée, pas de changement d'état.\n");
  printf("Défense : défense cotre un coup, vous suibissez pour les 2 prochains tours 66 pour cent des dégats normaux, stackable sur 5 tours.\n");
  printf("Esquive : esquive d'un coup. Reduction des dégats à 100 pour cent\n");
  printf("Labourage : Une chance de mettre a terre l'adversaire au prix d'attaquer en dernier.\n");
  printf("Coup de pied : attaque infligeant de lourds dégats au prix d'une précision moyenne.\n");

}


void affichage_stats(personnage p){
  /*On affichera les stats, on pourra voir aussi ceux des ennemis*/
  printf("%s est le nom du personnage\n", p->nom);
  printf("Vie / Vie Max : %d, %d\n", p->vie, p->vitalite);
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

void affichage_coup(coup cp){
  printf("l'attaque fera %d dégats\n", cp->degats);
  printf("l'attaque aura %d de précision\n", cp->precision);
  printf("l'attaque sera de priorité %d\n", cp->priorite);

  printf("Etat esquive est a %d\n", cp->pe_esquive);
  printf("Etat a terre est a %d\n", cp->pe_traterre);
  printf("Multiplicateur de dégats est à %d", cp->pe_multidmg);
  printf("Etat defensif est a %d\n", cp->pe_trdef);
  printf("Etat esquive est a %d\n", cp->en_esquive);
  printf("Etat a terre est a %d\n", cp->en_traterre);
  printf("Multiplicateur de dégats est à %d", cp->en_multidmg);
  printf("Etat defensif est a %d\n", cp->en_trdef);
}

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

  go = 0;
  vic = 0;
  continu = 1;
  p_prin= &principal;
  p_enne= &ennemi;
  coupp= &coupperso;
  coupe= &coupenne;

  principal = init_personnage();
  init_personnage_prin(p_prin);
  ennemi = init_personnage();
  init_personnage_enne(p_enne);
  printf("\nstats personnage \n");
  affichage_stats(p_prin);
  printf("\nstats ennemis \n");
  affichage_stats(p_enne);

  while(continu >= 1){
    init_personnage(p_enne);
    init_personnage_enne(p_enne);
    coupperso = init_coup();
    coupeenne = init_coup();
    while(go==0 && vic == 0){
      while(nbcoup>5){
        while (scanf("%d ",&nbcoup) != 1 && nbcoup <8 && nbcoup>=0){
          printf("quel sera votre coup?\n");
          printf("0 = attaque, 1 = defense, 2 = esquive\n");
          printf("3 = coup de pied, 4 = Mettre a terre, 5 = explications\n");
          printf("6 = Vos stats, 7 = stats ennemi\n");
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
      printf("coup choisis par le joueur : \n");
      affichage_coup(coupp);
      decisionia(coupe, p_enne, p_prin);
      printf("coup choisis par l'ordinateur : \n")
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
          p_prin -> vie = p_prin->vie + 15/100*p_prin->vitalite;
          if (p_prin->vie > p_prin->vitalite){
            p_prin->vie = p_prin->vitalite;
          }
        }
      }
    }
    vic =0;
    go = 0;
    while (scanf("%d ", &continu) != 1){
      printf("voulez vous continuez? \n");
    }
  }
  exit(1);
}
