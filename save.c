#include "save.h"



void sauvegarde(int *pts,int *nb_ligne,personnage p,personnage e){

  FILE* fichier = NULL;
  fichier = fopen("savegame.txt", "w");

  if(fichier==NULL){
      printf("Erreur lors de l'ouverture du fichier");
      exit(-1);
  }

  if (fichier != NULL){
    fprintf(fichier,"%s\n",p->nom);
    fputc(p->force,fichier);
    fputc(p->agilite,fichier);
    fputc(p->dexterite,fichier);
    fputc(p->vitalite,fichier);
    fputc(p->esquive,fichier);
    fputc(p->traterre,fichier);
    fputc(p->multidmg,fichier);
    fputc(p->trdef,fichier);
    fputc(*pts,fichier);
    fputc(*nb_ligne,fichier);




    fprintf(fichier,"%s\n",e->nom);
    fputc(e->force,fichier);
    fputc(e->agilite,fichier);
    fputc(e->dexterite,fichier);
    fputc(e->vitalite,fichier);
    fputc(e->esquive,fichier);
    fputc(e->traterre,fichier);
    fputc(e->multidmg,fichier);
    fputc(e->trdef,fichier);
    fputc(*pts,fichier);
    fputc(*nb_ligne,fichier);
    fclose(fichier);

  }

}
