
CC = gcc -std=c11
CFLAGS = -D_REENTRANT -g -W -Wall 
LDFLAGS = -lpthread

EXE = PhiloSem

all : $(EXE)

PhiloSem : PhiloSem.o Philo.o  semaphore.o simu.o
	$(CC) $(LDFLAGS) -o PhiloSem PhiloSem.o Philo.o  semaphore.o simu.o $(LDLIBS)
PhiloSem.o : PhiloSem.c  Philo.h simu.h semaphore.h
	$(CC) $(CFLAGS) -c PhiloSem.c


semaphore.o : semaphore.c semaphore.h
Philo.o : Philo.c Philo.h

simu.o : simu.c simu.h
	$(CC) $(CFLAGS)  -c simu.c

clean :
	-rm -f $(EXE) *.o
