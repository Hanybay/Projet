#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utilitaire.h"


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

personnages init_personnage();
void init_personnage_prin(personnage p);
void init_personnage_enne(personnage p,int nb_ligne);
void affichage_stats(personnage p);
void affichage_etats(personnage p);
void amelioration(int pts, personnage p)
