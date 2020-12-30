#include <stdlib.h>
#include <stdio.h>
#include "personnage.h"

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

coups init_coup();
void attaque(coup coupperso, personnage p, personnage e);
void defense (coup coupperso, personnage p, personnage e);
void esquive (coup coupperso, personnage p, personnage e);
void couppied(coup coupperso, personnage p, personnage e);
void labourage(coup coupperso, personnage p, personnage e);
void affichage_coup(coup cp);
