#include "save.h"



void sauvegarde(int *pts,int *nb_ligne,personnage p,personnage e){

  FILE* fichier = NULL;
  fichier = fopen("savegame.txt", "w");

  void sauvegarde(int *pts,int *nb_ligne,personnage p,personnage e){

  FILE* fichier = NULL;
  int c;
  fichier = fopen("savetest.txt", "w+");

  if(fichier==NULL){
      printf("Erreur lors de l'ouverture du fichier");
      exit(-1);
  }

  if (fichier != NULL){

    fprintf(fichier,"%s\n",p->nom);
    fprintf(fichier,"%d\n",p->vie);
    fprintf(fichier,"%d\n",p->force);
    fprintf(fichier,"%d\n",p->agilite);
    fprintf(fichier,"%d\n",p->dexterite);
    fprintf(fichier,"%d\n",p->vitalite);
    fprintf(fichier,"%d\n",p->esquive);
    fprintf(fichier,"%d\n",p->traterre);
    fprintf(fichier,"%d\n",p->multidmg);
    fprintf(fichier,"%d\n",p->trdef);
    fprintf(fichier,"%d\n",*pts);
    fprintf(fichier,"%d\n",*nb_ligne);




    fprintf(fichier,"%s\n",e->nom);
    fprintf(fichier,"%d\n",e->vie);
    fprintf(fichier,"%d\n",e->force);
    fprintf(fichier,"%d\n",e->agilite);
    fprintf(fichier,"%d\n",e->dexterite);
    fprintf(fichier,"%d\n",e->vitalite);
    fprintf(fichier,"%d\n",e->esquive);
    fprintf(fichier,"%d\n",e->traterre);
    fprintf(fichier,"%d\n",e->multidmg);
    fprintf(fichier,"%d\n",e->trdef);

    fclose(fichier);

  }

}
