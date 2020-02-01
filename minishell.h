void decouper(char *, char *, char **, int);
void addhist(char *, char **);
int comm(char *, char *, char **);

# define PROMPT printf("\x1b[1;34m%s@Minishell:\x1b[0m" "\x1b[1;32m%s\x1b[0m$ ", getenv("LOGNAME"), getcwd(pathname, MaxPathLength)) //Mon prompt personnalisé


enum {
  MaxLigne = 1024,              // longueur max d'une ligne de coms
  MaxMot = MaxLigne / 2,        // nbre max de mot dans la ligne
  MaxDirs = 100,		// nbre max de repertoire dans PATH
  MaxPathLength = 512,		// longueur max d'un nom de fichier
};
