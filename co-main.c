# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <assert.h>
# include <termios.h>
# include "minishell.h"

int main(int argc, char * argv[]){
  char ligne[MaxLigne];
  char pathname[MaxPathLength];
  char * mot[MaxMot];
  char * com[MaxMot];
  char * et[MaxMot];
  char * dirs[MaxDirs];
  char *hist[500];
  int i, j, status, tmp;
  //int e;

  /* Decouper PATH en repertoires */
  decouper(getenv("PATH"), ":", dirs, MaxDirs);

  /* Lire et traiter chaque ligne de commande */
  for(PROMPT; fgets(ligne, sizeof ligne, stdin) != 0; PROMPT){
    addhist(ligne, hist);
    decouper(ligne, ";", com, MaxMot); //Implémentation du ";"
    for(i = 0; com[i] != 0; i++){
      decouper(com[i], "&&", et, MaxMot); //Implémentation du "&&"
      for(j = 0; et[j] != 0; j++){
        decouper(et[j], " \t\n", mot, MaxMot);
        //printf("%d\n", appartient(com, "&")); Tentative infructueuse pour "&"

        if(!comm(et[j], mot[1], hist)){ //Test de la fonction qui gère les commandes

          if (mot[0] == 0)            // ligne vide
            continue;
          tmp = fork();               // lancer le processus enfant
          if (tmp < 0){
            perror("fork");
            continue;
          }
          if (tmp != 0){             // parent : attendre la fin de l'enfant
            while(wait(&status) != tmp);
            if (WEXITSTATUS(status)) //Si l'enfant a une erreur, alors sortie de la boucle
              break;
            continue;
          }
          /*for (e=0; mot[e] != 0; e++){ //Tentative infructueuse pour les redirections
            if(strcmp(mot[e], ">")){
              int fichier;
              fichier = fopen(mot[e+1], "w+");
              dup2(fd, 1);
              if(fichier == NULL)
                freopen(mot[e+1], "wb", fichier);
              for(i = 0; dirs[i] != 0; i++){
                snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
                execv(pathname, mot);
              }
            }
          }*/
              //enfant : exec du programme
          for(i = 0; dirs[i] != 0; i++){
            snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
            execv(pathname, mot);
          }
          //aucun exec n'a fonctionne
          fprintf(stderr, "%s: inconnu\n", mot[0]);
          exit(1);
        }
      }
    }
  }
  printf("Bye\n");
  return 0;
}
