
Shell: co-main.o cn-decouper.o commande.o
	gcc -Wall -o Shell co-main.o cn-decouper.o commande.o

co-main.o: co-main.c cn-decouper.c commande.c minishell.h
	gcc -Wall -o co-main.o -c co-main.c

cn-decouper.o: cn-decouper.c
	gcc -Wall -o cn-decouper.o -c cn-decouper.c

commande.o: commande.c
	gcc -Wall -o commande.o -c commande.c

clean:
	rm *.o*~core
