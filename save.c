#include "save.h"

void sauvegarde(int *pts,int *nb_ligne,personnage p,personnage e,int *vic,int *csoigner){

  FILE* fichier = NULL;
  int choix;
  choix = -1;

  do{
    printf("Dans quel slot souhaitez vous faire la sauvegarde?\n");
    printf("Slot 0, Slot 1, Slot 2\n");
    vider_buffer();
  }while(scanf("%d", &choix) <1 && (choix<0 || choix >3));

   switch(choix){
     case 0:
     fichier = fopen("savetest1.txt","w+");
       break;
     case 1:
     fichier = fopen("savetest2.txt","w+");
       break;
     case 2:
     fichier = fopen("savetest3.txt","w+");
       break;
    }




  if(fichier==NULL){
      printf("ce slot n'existe pas");
      exit(-1);
  }

  if (fichier != NULL){


fprintf(fichier,"%s\n",p->nom);
    fprintf(fichier,"%d\n",p->vie);
    fprintf(fichier,"%d\n",p->vitalite);
    fprintf(fichier,"%d\n",p->force);
    fprintf(fichier,"%d\n",p->agilite);
    fprintf(fichier,"%d\n",p->dexterite);
    fprintf(fichier,"%d\n",p->esquive);
    fprintf(fichier,"%d\n",p->traterre);
    fprintf(fichier,"%d\n",p->multidmg);
    fprintf(fichier,"%d\n",p->trdef);
    fprintf(fichier,"%d\n",*pts);
    fprintf(fichier,"%d\n",*nb_ligne);
    fprintf(fichier,"%d\n",*vic);
    fprintf(fichier,"%d\n",*csoigner);




    fprintf(fichier,"%s\n",e->nom);
    fprintf(fichier,"%d\n",e->vie);
    fprintf(fichier,"%d\n",e->vitalite);
    fprintf(fichier,"%d\n",e->force);
    fprintf(fichier,"%d\n",e->agilite);
    fprintf(fichier,"%d\n",e->dexterite);
    fprintf(fichier,"%d\n",e->esquive);
    fprintf(fichier,"%d\n",e->traterre);
    fprintf(fichier,"%d\n",e->multidmg);
    fprintf(fichier,"%d\n",e->trdef);

    fclose(fichier);

  }

}



void load_game(int *pts,int *nb_ligne,personnage p,personnage e,int *vic,int *csoigner){

  FILE* fichier = NULL;
  int choix;
  int retour = 0;
  choix = -1;
  while (retour !=2){
    do{
      printf("De quel slot souhaitez vous charger la sauvegarde?\n");
      printf("Slot 0, Slot 1, Slot 2, retour\n");
      vider_buffer();
    }while(scanf("%d", &choix) <1 && (choix<0 || choix >4));

     switch(choix){
       case 0:
       fichier = fopen("savetest1.txt","r");
       retour =1;
         break;
       case 1:
       fichier = fopen("savetest2.txt","r");
       retour =1;
         break;
       case 2:
       retour = 1;
       fichier = fopen("savetest3.txt","r");
         break;
      case 3:
      retour = 2;
        break;
    }

    if (retour != 2){
      if (fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier");
        retour = 0;
      }

      if (fichier != NULL){
        fscanf(fichier,"%s",p->nom);
        fscanf(fichier,"%d",&p->vie);
        fscanf(fichier,"%d",&p->vitalite);
        fscanf(fichier,"%d",&p->force);
        fscanf(fichier,"%d",&p->agilite);
        fscanf(fichier,"%d",&p->dexterite);
        fscanf(fichier,"%d",&p->esquive);
        fscanf(fichier,"%d",&p->traterre);
        fscanf(fichier,"%d",&p->multidmg);
        fscanf(fichier,"%d",&p->trdef);
        fscanf(fichier,"%d",pts);
        fscanf(fichier,"%d",nb_ligne);
        fscanf(fichier,"%d",vic);
        fscanf(fichier,"%d",csoigner);




        fscanf(fichier,"%s",e->nom);
        fscanf(fichier,"%d",&e->vie);
        fscanf(fichier,"%d",&e->vitalite);
        fscanf(fichier,"%d",&e->force);
        fscanf(fichier,"%d",&e->agilite);
        fscanf(fichier,"%d",&e->dexterite);
        fscanf(fichier,"%d",&e->esquive);
        fscanf(fichier,"%d",&e->traterre);
        fscanf(fichier,"%d",&e->multidmg);
        fscanf(fichier,"%d",&e->trdef);
        retour = 2;
      }
    }
  }
  fclose(fichier);
}
