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
  int retour;
  retour =0;
  choix = -1;
  while (retour !=2){
    do{
      printf("De quel slot souhaitez vous charger la sauvegarde?\n");
      printf("Slot 0, Slot 1, Slot 2, retour\n");
    }while(scanf("%d", &choix) <1 && (choix<0 || choix >4));
    vider_buffer();
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
        printf("Il n'y a pas de sauvegarde a cet emplacement! \n\n");
        retour = 0;
      }

      if (fichier != NULL){
        if(fscanf(fichier,"%s",p->nom)!= 1){
          printf("erreur\n");
        }
        if(fscanf(fichier,"%d",&p->vie)!= 1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->vitalite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->force)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->agilite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->dexterite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->esquive)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->traterre)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->multidmg)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&p->trdef)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",pts)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",nb_ligne)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",vic)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",csoigner)!=1){
    printf("erreur\n");
  }




  if(fscanf(fichier,"%s",e->nom)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->vie)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->vitalite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->force)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->agilite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->dexterite)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->esquive)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->traterre)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->multidmg)!=1){
    printf("erreur\n");
  }
  if(fscanf(fichier,"%d",&e->trdef)!=1){
    printf("erreur\n");
    retour = 2;
      }
    }
    if (fichier !=NULL){
      fclose(fichier);
    }
  }
}
}
