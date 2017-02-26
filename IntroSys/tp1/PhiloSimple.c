
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
int est_libre[MAXPHILOS]={1,};

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

    while (!est_libre[g]) {}
      /* j'ai pris fourchette G */
    printf("Philo %d a pris la fourchette gauche\n", no);
    est_libre[g]=0;

    while (!est_libre[d]) {}
      /* j'ai pris fourchette D */
    printf("Philo %d a pris la fourchette droite\n", no);
    est_libre[d]=0;

}

void Liberer_fourchettes (int no)
{
    int g;
    int d;
    g = FourchetteGauche (no);
    d = FourchetteDroite (no);

    printf("Philo %d pose les fourchettes\n", no);
    est_libre[g]=1;
    est_libre[d]=1;
}

void *CodePhilo (void *a)
{
    int no;
    no = ((philo *) a)->no;
    while (1) {
        /* Pense */	
        printf("Le philosophe %d pense\n", no);
        DormirAleatoire (no, MinDelayPense, MaxDelayPense);

        /* Demande */
	printf("Le philosophe %d demande a manger\n", no);
        Demander_fourchettes (no);

        /* Mange */
        printf("Le philosophe %d mange\n", no);
        DormirAleatoire (no, MinDelayMange, MaxDelayMange);

        Liberer_fourchettes (no);
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
	est_libre[i]=1;
    }
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
