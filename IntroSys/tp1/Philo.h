/* Time-stamp: <08 Nov 2000 10:59 queinnec@enseeiht.fr> */

/* Copyright 2000 ENSEEIHT. */ 

#ifndef _PHILO_H
#define _PHILO_H

#define MAXPHILOS 30

/* Les états d'un philosophe. */
typedef enum {
    Philo_Pense, Philo_Demande, Philo_Mange
} Philo_EtatPhi;

/* Les états d'une fourchette. */
typedef enum {
    Philo_Table, Philo_AssietteGauche, Philo_AssietteDroite
} Philo_EtatFour;

/* Initialisé depuis la ligne de commande par philoInit */
extern int nbPhilosophes;

/* PhiloDroite est le numéro du philosophe à droite de no. */
int PhiloDroite (int no);
/* PhiloGauche est le numéro du philosophe à gauche de no. */
int PhiloGauche (int no);

/* FourchetteDroite est le numéro de la fourchette de droite du philo no. */
int FourchetteDroite (int no);
/* FourchetteGauche est le numéro de la fourchette de gauche du philo no. */
int FourchetteGauche (int no);

void philoInit (int argc, char **argv);

#endif
