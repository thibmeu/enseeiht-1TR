
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "Philo.h"
#include "semaphore.h"
#include "simu.h"

/* Chaque philosophe mange entre MinDelayMange et MaxDelayMange secondes, et
 * pense entre MinDelayPense et MaxDelayPense (les deux bornes incluses). */
#define MinDelayMange  5
#define MaxDelayMange  20
static int MinDelayPense; /*  5 */
static int MaxDelayPense; /* 20 */

/* Pas de synchro -> on test si la fourchette est libre ou pas */
semaphore_t est_libre[MAXPHILOS];
semaphore_t aTable;
semaphore_t philoBloque[MAXPHILOS];
semaphore_t mutex;
Philo_EtatPhi etatPhilo[MAXPHILOS];

/* Un philosophe.
 * Il s'agit de l'information qui permet à chaque philosophe de
 * savoir qui il est.  On pourrait en outre y trouver des
 * informations relatives à la synchronisation (par exemple l'état).
 */
typedef struct {
    int no;
} philo;

/* Le tableau des philosophes. */
static philo *lesPhilos[MAXPHILOS];

void DormirAleatoire (int no, int bi, int bs)
{
    if (bi <= bs)
      simu_sleep (no, random () % (bs - bi + 1) + bi);
}

/* Utilisé par PhiloX. */
void set_sleep_duration (int intensite)
{
    switch (intensite) {
      case 0:                   /* Peu gourmands */
        MinDelayPense = 20 * MinDelayMange;
        MaxDelayPense = 20 * MaxDelayMange;
        break;
      case 1:                   /* Assez gourmands */
        MinDelayPense = 5 * MinDelayMange;
        MaxDelayPense = 5 * MaxDelayMange;
        break;
      case 2:                   /* gourmands (initial) */
        MinDelayPense = MinDelayMange;
        MaxDelayPense = MaxDelayMange;
        break;
      case 3:                   /* Très gourmands */
        MinDelayPense = (MinDelayMange + 1) / 3;
        MaxDelayPense = (MaxDelayMange + 1) / 3;
        break;
      case 4:                   /* Extrêmement gourmands */
        MinDelayPense = (MinDelayMange + 1) / 8;
        MaxDelayPense = (MaxDelayMange + 1) / 8;
        break;
      default:
        printf ("Frequence de sommeil hors des bornes.\n");
    }
    /* printf ("Delai pense = %d-%d, utilise = %d-%d\n",
            MinDelayPense, MaxDelayPense, MinDelayMange, MaxDelayMange);
    */
}

/****************************************************************/

void Demander_fourchettes (int no)
{
    int g;
    int d;
    g = FourchetteGauche (no);
    d = FourchetteDroite (no);

    sem_P(est_libre[g]);
      /* j'ai pris fourchette G */
    printf("Philo %d a pris la fourchette gauche\n", no);

    sem_P(est_libre[d]);
      /* j'ai pris fourchette D */
    printf("Philo %d a pris la fourchette droite\n", no);

}

void Liberer_fourchettes (int no)
{
    int g;
    int d;
    g = FourchetteGauche (no);
    d = FourchetteDroite (no);

    printf("Philo %d pose les fourchettes\n", no);
    sem_V(est_libre[g]);
    sem_V(est_libre[d]);
}

void *CodePhilo (void *a)
{
    int no;
    no = ((philo *) a)->no;
    while (1) {
        /* Pense */	
        printf("Le philosophe %d pense\n", no);
        etatPhilo[no] = Philo_Pense;
        DormirAleatoire (no, MinDelayPense, MaxDelayPense);
        
        /* On limite le nombre de personnes a table */
        sem_P(aTable);

        /* Demande */
	    printf("Le philosophe %d demande a manger\n", no);
        etatPhilo[no] = Philo_Demande;
        Demander_fourchettes (no);

        sem_P(mutex);
        if (etatPhilo[PhiloGauche(no)] == Philo_Mange || etatPhilo[PhiloDroite(no)] == Philo_Mange)
            sem_P(philoBloque[no]);
        sem_V(mutex);

        /* Mange */
        printf("Le philosophe %d mange\n", no);
        etatPhilo[no] = Philo_Mange;

        DormirAleatoire (no, MinDelayMange, MaxDelayMange);

        sem_P(mutex);
        Liberer_fourchettes (no);

        if (etatPhilo[PhiloGauche(PhiloGauche(no))] != Philo_Mange)
            sem_V(philoBloque[PhiloGauche(no)]);
        if (etatPhilo[PhiloDroite(PhiloDroite(no))] != Philo_Mange)
            sem_V(philoBloque[PhiloDroite(no)]);
        sem_V(mutex);

        sem_V(aTable);
    }
    /* NOTREACHED */
    return NULL;

}

void InitialiserPhilo (void)
{
    int i;
    for (i = 0; i < nbPhilosophes; i++) {
        lesPhilos[i] = malloc (sizeof (philo));
        lesPhilos[i]->no = i;

	/* Au depart, les fourchettes sont libres */
	    est_libre[i] = sem_init(1);
	    philoBloque[i] = sem_init(1);
    }

    aTable = sem_init(nbPhilosophes-1);
    mutex = sem_init(1);

    for (i = 0; i < nbPhilosophes; i++) {
        pthread_t t;
        pthread_create (&t, NULL, CodePhilo,lesPhilos[i]);
    }

}

int main (int argc, char **argv)
{
    philoInit (argc, argv);
    srandom (getpid());
    set_sleep_duration (4);
    simu_init (nbPhilosophes);
    InitialiserPhilo ();
 
    for (;;);
}
