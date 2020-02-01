# include <stdio.h>
# include <string.h>
#include <unistd.h>
#include <stdlib.h>

void addhist(char *commande, char *hist[]){ //Permet d'incrémenter l'historique
  int i;
  for(i=0 ; i<500 ; i++){
    if(hist[i] == 0){
      hist[i] = malloc(strlen(commande)+1);
      strcpy(hist[i],commande);
      return;
    }
  }
  for(i=0 ; i<500 - 1; i++){
    strcpy(hist[i],hist[i+1]);
  }
  strcpy(hist[500 - 1],commande);
}
void affhist(char *hist[]){ //Permet d'afficher l'historique
  int i;
  for(i=0 ; i<500 && hist[i]!=0 ; i++){
    printf("%d %s", i+1, hist[i]);
  }
}

int comm(char * commande, char * mot, char *hist[]){ //Fonction qui prend en charge les commandes
  if (!strcmp(commande, "cd")){ //Commande cd
    if (mot == NULL){
      chdir("/."); //S'il n'y a pas de répertoire spécifié, retour à la racine
      return 1;
    }
    if (chdir(mot) == -1)
      printf("%s : Ce dossier n'existe pas.\n", mot); //Si le dossier n'existe pas
    return 1;
  }
  if (!strcmp(commande, "exit")){ //Commande exit
    exit(0);
  }
  if (!strcmp(commande, "history")){ //Commande de l'historique
    affhist(hist);
    return 1; 
  }
  return 0;
}

int appartient(char **commande, char *c){ //Commande qui teste si un mot appartient à un char
  int i;
  for (i=0; commande[i] != 0; i++){
    if(!strcmp(commande[i], c)){
      return 1;
    }
  }
  return 0;
}
