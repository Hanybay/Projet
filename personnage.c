#include "personnage.h"

personnages init_personnage(){
  personnages p;
  int i;
  for (i=0; i<19; i++){
    p.nom[i]='\0';
  }
  p.force = 45 + aleat(-10, 10);  /*Les stats sont tiré aléatoirement a chaque nouvelle partie*/
  p.agilite = 45 + aleat(-10, 10);  /*ennemi comme personnage principal*/
  p.dexterite = 45 + aleat(-10, 10);
  p.vitalite = 500 + aleat(-50, 50);
  p.vie = p.vitalite; /*A l'initialisation Pv = Pv max*/
  p.trdef = 0;
  p.esquive = 0;
  p.traterre=0;
  p.multidmg=100;
  return p;
}

void init_personnage_prin(personnage p){
  char string[255];
  int i;
  printf("Le nom de votre personnage en 19 lettres ou moins?  ");
  while(scanf("%s", string)<1){
    printf("Le nom de votre personnage en 19 lettres ou moins?  ");
    vider_buffer();
  }
  for(i=0; i<19 && string[i]!='\0';i++){
    p->nom[i]=string[i];
  }
     /*Afin de rentrer le prénom, il faudra rentrer*/
}

void init_personnage_enne(personnage p,int *nb_ligne){
  int i;
  int j, difficulte;
  FILE* fichier = NULL;
  fichier = fopen("perso.txt","r");

  difficulte = (*nb_ligne)/3;
  if (difficulte >400){
    difficulte = 400;
  }
  j = ( *nb_ligne % 13) + 1;



  if(fichier==NULL){
    printf("erreur");
    exit(-1);
  }

if (fichier != NULL){
  for(i = 0; i < j; i++){
    if(fscanf(fichier, "%s", p->nom)!=1){
      printf("erreur\n");
    }
  }
  fclose(fichier);
  }
  p->force = 45 + aleat(-10+difficulte/2, 10+difficulte/2);  /*Les stats sont tiré aléatoirement a chaque nouvelle partie*/
  p->agilite = 45 + aleat(-10+difficulte/2, 10+difficulte/2);  /*ennemi comme personnage principal*/
  p->dexterite = 45 + aleat(-10+difficulte/2, 10+difficulte/2);
  p->vitalite = 500 + aleat(-50+(difficulte*9), 50+(difficulte*81)) + difficulte*81;
  p->vie = p->vitalite; /*A l'initialisation Pv = Pv max*/
  p->trdef = 0;
  p->esquive = 0;
  p->traterre=0;
  p->multidmg=100;
}

void affichage_stats(personnage p){
  /*On affichera les stats, on pourra voir aussi ceux des ennemis*/
  printf("%s est le nom du personnage\n", p->nom);
  printf("Vie / Vie Max : %d/%d\n", p->vie, p->vitalite);
  printf("Force : %d\n", p->force);
  printf("Agilite : %d\n", p->agilite);
  printf("Dexterite : %d\n", p->dexterite);
}

void affichage_etats(personnage p){
  printf("%s a les etats suivants :\n", p->nom);
  printf("etat esquive est a %d\n", p->esquive);
  printf("etat a terre est a %d\n", p->traterre);
  printf("Multiplicateur de dégats est à %d", p->multidmg);
  printf("Etat defensif est a %d\n", p->trdef);
}


void amelioration(int *pts, personnage p, int *asave, int *vic, int *csoigner){
  int confirmer;
  int choix;
  confirmer = 0;
  choix = -1;
  if (*csoigner!=1){
    p -> vie = p->vie + ((10*p->vitalite)/100);
    if (p->vie > p->vitalite){
      p->vie = p->vitalite;
    }
    *csoigner=1;
  }
  printf ("Voici le menu d'amélioration pour le personnage:\n");
  printf ("Le menu d'amélioration vous permettera de vous donner des statistiques supplémentaires\n");
  printf("Améliorer les point de vie max de 25 coutera 3 points, vous guérir de 15 pourcent de la vie coutera 1 points\n");
  printf("Le reste coutera 2 points pour chaque amélioration de 1\n");
  printf("Notez que chaque entree au menu d'amelioration vous regènera de 10 pourcent de votre vie maximum\n\n");
  while (confirmer==0){
    do{
      printf("   0 : Vie max, cout 3 points; 1 : soin 15 pour cent de vie, cout 1 point\n");
      printf("   2 : +1 force, 3:  +1 agilité, 4: +1 dexterite; cout 2 points\n");
      printf("   5 : regarder vos statistiques; 6 : quitter le menu d'amélioration\n");
      printf("   7 : Sauvegarder et quitter\n\n");
      printf("Vous avez actuellement %d point(s)\n", *pts);
      printf("Que voulez vous améliorer?\n");
    } while(scanf("%d", &choix) <1 && (choix<0 || choix >8));
    vider_buffer();
    switch(choix){
      case 0:
        if(p->vitalite==Vie_max){
          printf("Vous êtes déjà à la valeur maximal!\n");
        }
        else{
          if(*pts<3){
            printf("vous n'avez pas assez de points!\n");
          }
          else{
            *pts-=3;
            p->vitalite = p->vitalite + 25;
            p->vie = p->vie +25;
            if(p->vitalite >Vie_max){
              p->vitalite = Vie_max;
            }
            if(p->vie >Vie_max){
              p->vie = Vie_max;
            }
            printf("Vous avez utiliser 3 points afin de vous augmentez la vie maximum\n");
            printf("voici vos nouvelles statistiques : Vie/Vie_max,  %d/%d\n", p->vie, p->vitalite);
          }
        }
        break;
      case 1:
        if (p->vie==p->vitalite){
          printf("Vos pv sont déjà au maximum!\n");
        }
        else{
          if (*pts<1){
            printf("Vous n'avez pas assez de points!\n");
          }
          else{
            *pts-=1;
            p -> vie = p->vie + ((p->vitalite*15)/100);
            if (p->vie > p->vitalite){
              p->vie = p->vitalite;
            }
            printf("Voilà vos nouvelles statistiques: Vie/Vie_max,  %d/%d\n", p->vie, p->vitalite);
          }
        }
        break;
      case 2:
        if(p->force==Valeur_max){
          printf("Vous êtes déjà à la valeur maximal!\n");
        }
        else{
          if(*pts<2){
            printf("vous n'avez pas assez de points!\n");
          }
          else{
            *pts-=2;
            p->force = p->force + 1;
            printf("Vous avez utiliser 2 points afin de vous augmentez la force\n");
            printf("voici vos nouvelles statistiques : Force = %d\n", p->force);
          }
        }
        break;
      case 3:
        if(p->agilite==Valeur_max){
          printf("Vous êtes déjà à la valeur maximal!\n");
        }
        else{
          if(*pts<2){
            printf("vous n'avez pas assez de points!\n");
          }
          else{
            *pts-=2;
            p->agilite = p->agilite + 1;
            printf("Vous avez utiliser 2 points afin de vous augmentez la force\n");
            printf("voici vos nouvelles statistiques : Agilite = %d\n", p->agilite);
          }
        }
        break;
      case 4:
        if(p->dexterite==Valeur_max){
          printf("Vous êtes déjà à la valeur maximal!\n");
        }
        else{
          if(*pts<2){
            printf("vous n'avez pas assez de points!\n");
          }
          else{
            *pts-=2;
            p->dexterite = p->dexterite + 1;
            printf("Vous avez utiliser 2 points afin de vous augmentez la force\n");
            printf("voici vos nouvelles statistiques : Dexterite = %d\n", p->dexterite);
          }
        }
        break;
      case 5:
        affichage_stats(p);
        break;
      case 6:
        confirmer=1;
        *csoigner = 0;
        *vic =0;
        break;
      case 7:
        confirmer = 1;
        *asave =1;
        break;
    }
    choix = -1;
    printf("\n");
  }
}
