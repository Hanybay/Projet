#include "tour.h"

void decisionia(coup a, personnage ia, personnage perso){
  int decision;
  decision = aleat(0, 100);
  if (decision<60){
    attaque(a, ia, perso);
  }
  if(decision<80 && decision>=60){
    defense(a, ia, perso);
  }
  if(decision<100 && decision>=80){
    esquive(a, ia, perso);
  }
  /*
  if(decision<80 && decision>=60){
    couppied(a, ia, perso);
  }
  if(decision<=100 && decision>=80){
    labourage(a, ia, perso);
  }
}
*/
}

void calcul_attaque(coup a, personnage aa, personnage bb){
  int precis, dmg;
  precis = aleat(0,100);
  printf("%d est a ce point précis!\n", precis);
  /*La precision est calculé en lancant 1d100. Bien qu'on peut largement dépassé*/
  if (bb->esquive == 1){
    a->precision = a->precision - bb->agilite;
    printf("%s est dans l'état esquive! \n\n", bb->nom);
    printf("%d de precision sur le coup de %s\n", a->precision, aa->nom);
    /*le debuff de précision par l'esquive  est ici*/
    if (a->precision <10){
      a->precision = 10;
    /*La précision ne pas être plus bas que "10%""*/
    }
  }
  if(a -> precision >= precis){
    /*Si l'attaque réussi, alors tout est appliqué*/
    dmg = a -> degats*aa->multidmg/100;
    bb -> vie -= dmg;
    if(dmg>0){
      printf("%s a perdu %d pvs!\n", bb->nom, dmg);
    }
    /*Etat allie*/
    aa->trdef += a->pe_trdef;
    if(a->pe_trdef>0){
      printf("%s se défend, les dégats sont réduit pendant 2 tours!\n", aa->nom);
    }
    aa->esquive = a->pe_esquive;
    if(a->pe_esquive>0){
      printf("%s se met en posture d'esquive!\n", aa->nom);
    }
    aa->multidmg = aa->multidmg * a->pe_multidmg/100;
    aa->traterre += a->pe_traterre;
    /*Etats ennemis*/
    bb -> trdef += a -> en_trdef;
    bb -> esquive += a -> en_esquive;
    bb -> multidmg = bb -> multidmg * a ->en_multidmg/100;

    if(bb->traterre ==0){
      bb -> traterre += a -> en_traterre;
      if (bb->traterre >0){
        printf("%s est en position de faiblesse pendant 2 tours! Profitez en!\n", bb->nom);
      }
    }
  }
  else{
    /*Si l'attaque ne réussi pas, et que l'esquive à réussi*/
    if(bb -> esquive == 1 && a -> degats !=0){
      printf("%s a esquivé l'attaque de %s ! Il passe en contre-attaque!\n", bb->nom, aa->nom);
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
  a->multidmg =100;
  b->multidmg = 100;

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
  };
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
    b -> multidmg = b -> multidmg*3;
    a -> traterre -= 1;
  }
  if (b->traterre > 0){
    a->multidmg = a->multidmg*3;
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
      srand(time(NULL));
      calcul_attaque(b, bb, aa);
      if (aa->vie >0){
        srand(time(NULL));
        calcul_attaque(a, aa, bb);
      }
    }
  }
  /*On applique la fin de tour*/
  findetour(aa, bb);
}