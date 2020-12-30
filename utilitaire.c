#include "utilitaire.h"



int aleat(int x, int y){
  int alea;
  alea = rand()%(y-x+1)+x; /*On aura besoin de cette fonctions pour beaucoup de choses*/
  return alea;
}

void vider_buffer(){
  int c;
  do{
    c=getchar();
  }while(c!=EOF&&c!='\n');
}

void explication(){
  printf("Pour jouer à notre fabuleux jeux, vous disposez d'une action parmis 5 chaque tour.\n");
  printf("Attaque : attaque normal, les dégats sont sur la force brut,précision elevée, pas de changement d'état.\n");
  printf("Défense : défense cotre un coup, vous suibissez pour les 2 prochains tours 66 pour cent des dégats normaux, stackable sur 5 tours.\n");
  printf("Esquive : esquive d'un coup. Reduction des dégats à 100 pour cent\n");
  printf("Labourage : Une chance de mettre a terre l'adversaire au prix d'attaquer en dernier.\n");
  printf("Coup de pied : attaque infligeant de lourds dégats au prix d'une précision moyenne.\n");

}
