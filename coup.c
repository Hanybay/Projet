#include "coup.h"

coups init_coup(){
  coups cp;
  cp.degats = 0; /*Tout est à 0 pour l'initialisation d'un coup a part le multiplicateur*/
  cp.pe_trdef = 0;
  cp.pe_esquive =0;
  cp.en_multidmg = 100;
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
  coupperso -> precision = 80 + p->dexterite - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Etats allie*/
  /*Pour une attaque normale, il n'y a aucun buff*/
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive =0;

  /*Etats ennemis*/
  /*Pour une attaque normale, il n'y a aucun malus*/
  coupperso->en_multidmg = 100;
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

  if (p->trdef<1){
    coupperso->en_multidmg = 66;
  }
  else{
    coupperso->en_multidmg = 100;
  }
  coupperso->en_traterre = 0;

  /*Etats allie*/
  /*La défense donne un "buff" de défense sur plusieurs tour*/
  coupperso->pe_trdef = 2;
  coupperso->pe_esquive = 0;


}

void esquive (coup coupperso,personnage p, personnage e){
  /*Degats*/
  coupperso->degats = 0;
  /*Les dégats d'une esquive sont = à 0*/

  /*Priorite*/
  coupperso->priorite = ((p -> agilite) + (p -> dexterite)*1/4)*1.5;
  /*la priortité est plus elevé qu'une attaque, en espérant être plus rapide que l'ennemi*/

  /*Precision de l'attaque, le minimum sera 10%, il n'y a pas de maximum defini*/
  coupperso->precision = 30 + p->dexterite*2 - e->agilite;
  /*La précision est proportionnel à la dexterite et sera contrecarré par l'agilite ennemi*/

  /*Etats allie */
  /*Inflige un buff d'agilité, correspondant a un malus de précision pour l'ennemi*/
  coupperso->pe_trdef = 0;
  coupperso->pe_esquive = 1;

  /* Etats ennemi */
  /*il n'y a pas de malus supplementaire pour l'ennemi*/

  coupperso->en_multidmg = 100;
  coupperso->en_traterre = 0;
}

void couppied(coup coupperso, personnage p, personnage e){ /* p = Attaquant, e = Attaqué*/
  /*Degats*/
  coupperso -> degats = ((p -> force)/4 + p->dexterite)*1.5;
  /*Les dégats sont proportionnel a la dexterite et un peu a la force, les dégats peuvent être puissant*/

  /*priorite*/
  coupperso -> priorite = (p -> agilite) + (p -> dexterite)*1/4;
  /*Priorité normale*/

  /*Precision*/
  coupperso -> precision = 20 + p -> dexterite*1.5 - e -> agilite;
  /*La priorité de base est basse, mais si la dexterite est bien monte, ce ne sera pas un probleme*/

  /*Etats allie*/
  /*L'attaque, ne donne aucun bonus*/
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive =0;

  /*Etats ennemis*/
  /*L'attaque n'inflige aucun Malus*/
  coupperso -> en_multidmg = 100;
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
  coupperso -> precision = 30 + p -> dexterite - e -> agilite;
  /*La précision est moyenne, et sera aussi en fonction des pvs*/

  /*Etats allie*/
  coupperso -> pe_trdef = 0;
  coupperso -> pe_esquive = 0;

  /*Etats ennemis*/
  /*inflige un malus, si c'est le cas, les dégats seront multiplié au prochain tours*/
  coupperso -> en_multidmg = 100;
  coupperso -> en_traterre = 2;
}

void affichage_coup(coup cp){
  printf("l'attaque fera %d dégats\n", cp->degats);
  printf("l'attaque aura %d de précision\n", cp->precision);
  printf("l'attaque sera de priorité %d\n\n", cp->priorite);

  printf("Etat esquive est a %d\n", cp->pe_esquive);
  printf("Etat defensif est a %d\n\n", cp->pe_trdef);

  printf("Etat a terre est a %d\n", cp->en_traterre);
  printf("Multiplicateur de dégats est à %d\n\n", cp->en_multidmg);
}
