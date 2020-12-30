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
  printf("Le nom de votre personnage en 19 lettres ou moins?  ");
  while(scanf("%s ", p->nom)<1){
    printf("Le nom de votre personnage en 19 lettres ou moins?  ");
    vider_buffer();
  }
     /*Afin de rentrer le prénom, il faudra rentrer*/
}

void init_personnage_enne(personnage p,int nb_ligne){
int i;
int j = (nb_ligne mod 12) + 1;
FILE* fichier = NULL;
fichier = fopen("perso.txt","r");

if(fichier==NULL){
  printf("erreur");
  exit(-1);
}

  if (fichier != NULL){
  for(i = 0; i < nb_ligne; i++){
    fscanf(fichier, "%s", p->nom);
    }
  fclose(fichier);
  }
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

void init_personnage_enne(personnage p){
  p->nom[0] = 'M';
  p->nom[1] = 'i';
  p->nom[2] = 'c';
  p->nom[3] = 'h';
  p->nom[4] = 'e';
  p->nom[5] = 'l';
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
  printf("Multiplicateur de dégats est à %d\n", p->multidmg);
  printf("Etat defensif est a %d\n", p->trdef);
}

void amelioration(int *pts, personnage p){
  int confirmer;
  int choix;
  confirmer = 0;
  choix = -1;
  printf ("Voici le menu d'amélioration pour le personnage\n");
  printf ("Le menu d'amélioration vous permettera de vous donner des statistiques supplémentaires\n");
  printf("Améliorer les point de vie max de 25 coutera 3 points, vous guérir de 30 pourcent de la vie coutera 1 points\n");
  printf("Le reste coutera 2 points pour chaque amélioration de 1\n");
  printf("Notez que chaque entree au menu d'amelioration vous regènera de 15 pourcent de votre vie maximum");
  while (confirmer==0){
    do{
      printf("Que voulez vous améliorer?");
      printf("0 : Vie max, cout 3 points; 1 : soin 30 pour cent de vie, cout 1 point");
      printf("2 : +1 force, 3:  +1 agilité, 4: +1 dexterite; cout 2 points");
      printf("5 : regarder vos statistiques; 6 : quitter le menu d'amélioration");
      printf("Vous avez actuellement %d point(s)", pts);
      vider_buffer();
    } while(scanf("%d", &choix) <1 && (choix<0 || choix >7));
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
          printf("Vos pv sont déjà au maximum!");
        }
        else{
          if (*pts<1){
            printf("Vous n'avez pas assez de points!");
          }
          else{
            *pts-=1;
            p -> vie = p->vie + 30/100*p->vitalite;
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
        break;
    }
    choix = -1;
  }
}
