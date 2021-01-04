

#include "save.h"

void save_score(int *scoring){
  /*Charger et afficher les fichier sauvegarder*/
  int tab_score[10];
  int i;
  int j = 0;
  int k = 0;

  FILE* fichier = NULL;
  fichier = fopen("score.txt","r+");
  for(i=0; i < 10;i++){
    if(fscanf(fichier,"%d\n",&tab_score[i])!=1){
      printf("%d erreur\n",i);
    }
  }
  for(i=0; i < 10;i++){
    k = i;
    if(tab_score[i] < *scoring){
      j = tab_score[i];
      tab_score[i] = *scoring;
      i = 11;
    }
  }
  for(i=k+1; i<10;i++){
    k = tab_score[i];
    tab_score[i] = j;
    j = k;
  }
  fclose(fichier);
  fichier = fopen("score.txt","r+");

  if(fichier==NULL){
    printf("ce slot n'existe pas");
    exit(-1);
  }

  if (fichier !=NULL){
    for(i = 0; i < 10; i++){
      fprintf(fichier, "%d\n",tab_score[i]);
    }
  }
  fclose(fichier);
}




void sauvegarde(int *pts,int *nb_ligne,personnage p,personnage e,int *vic,int *csoigner, int *scoring){

  FILE* fichier = NULL;
  int choix;
  int retour;
  retour = 0;
  choix = -1;
  while (retour !=2){
    do{
      printf("Dans quel slot souhaitez vous sauvegarder la partie?\n");
      printf("Slot 0, Slot 1, Slot 2, retour\n");
    }while(scanf("%d", &choix) <1 && (choix<0 || choix >4));
    vider_buffer();
    switch(choix){
      case 0:
      fichier = fopen("save0.txt","w+");
      retour =1;
      break;
      case 1:
      fichier = fopen("save1.txt","w+");
      retour =1;
      break;
      case 2:
      retour = 1;
      fichier = fopen("save2.txt","w+");
      break;
      case 3:
      retour = 2;
      break;
    }

    if (retour != 2){
      if (fichier == NULL){
        printf("Impossible de sauvegarder à cet emplacement! \n\n");
        retour = 0;
      }

    }

    if (retour != 2){
      if (fichier == NULL){
        printf("Il n'y a pas de sauvegarde à cet emplacement! \n\n");
        retour = 0;
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
        fprintf(fichier,"%d\n",*scoring);




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
        save_score(scoring);

      }

    }
    retour = 2;
  }
}



void load_game(int *pts,int *nb_ligne,personnage p,personnage e,int *vic,int *csoigner, int *scoring){
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
      fichier = fopen("save0.txt","r");
      retour =1;
      break;
      case 1:
      fichier = fopen("save1.txt","r");
      retour =1;
      break;
      case 2:
      retour = 1;
      fichier = fopen("save2.txt","r");
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
        if(fscanf(fichier,"%d",scoring)!=1){
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
          choix  = -1;
        }
      }
      if (fichier !=NULL){
        fclose(fichier);
      }
      retour = 2;
    }
  }
}
