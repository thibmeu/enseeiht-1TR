/* Time-stamp: <09 Oct 2002 09:45 queinnec@enseeiht.fr> */

/* Copyright 2000 ENSEEIHT. */ 

#include <stdlib.h>
#include <stdio.h>
#include "Philo.h"

/* Initialisés depuis la ligne de commande par philoInit */
int nbPhilosophes;

/* PhiloDroite est le numéro du philosophe à droite de no. */
int PhiloDroite (int no)
{
    if (no == 0)
      return nbPhilosophes - 1;
    else
      return no - 1;
}

/* PhiloGauche est le numéro du philosophe à gauche de no. */
int PhiloGauche (int no)
{
    if (no == nbPhilosophes - 1)
      return 0;
    else
      return no + 1;
}

/* FourchetteDroite est le numéro de la fourchette de droite du philo no. */
int FourchetteDroite (int no)
{
    return no;
}

/* FourchetteGauche est le numéro de la fourchette de gauche du philo no. */
int FourchetteGauche (int no)
{
    if (no == nbPhilosophes - 1)
      return 0;
    else
      return no + 1;
}

void philoInit (int argc, char **argv)
{
    if (argc != 2) {
        fprintf (stderr, "Philo <nb philos>\n");
        exit (1);
    }
    nbPhilosophes = atoi (argv[1]);
    if ((nbPhilosophes < 2) || (nbPhilosophes > MAXPHILOS)) {
        fprintf (stderr, "nb philo dans [2..%d]\n", MAXPHILOS);
        exit (1);
    }
}
