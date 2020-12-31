CC=gcc
CFLAGS=-W -Wall -pedantic




general : utilitaire.o tour.o coup.o personnage.o save.o general.o
	$(CC) $(CFLAGS) utilitaire.o tour.o coup.o personnage.o save.o general.o -o general


utilitaire.o : utilitaire.c utilitaire.h
	$(CC) $(CFLAGS) -c utilitaire.c

tour.o : tour.c tour.h
	$(CC) $(CFLAGS) -c tour.c

coup.o : coup.c coup.h
	$(CC) $(CFLAGS) -c coup.c

personnage.o : personnage.c personnage.h
	$(CC) $(CFLAGS) -c personnage.c

save.o : save.c save.h
	$(CC) $(CFLAGS) -c save.c

general.o : general.c personnage.h coup.h utilitaire.h tour.h save.h
	$(CC) $(CFLAGS) -c general.c
