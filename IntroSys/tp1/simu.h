/* Time-stamp: <08 Nov 2000 16:50 queinnec@enseeiht.fr> */

/* Copyright 2000 ENSEEIHT. */ 

#ifndef _SIMU_H_
#define _SIMU_H_

/* Simulateur temporel, avec possibilité de suspendre l'écoulement du temps,
 * de varier la vitesse du temps, et d'interrompre un sommeil.
 */

/* Initialise le simulateur de temps pour `nbproc' processus. */
void simu_init (int nbproc);

/* Suspend l'exécution du processus appelant, qui s'identifie par `noproc',
 * pour la durée spécifiée. */
void simu_sleep (int noproc, int duree);

/* Interrompt le sommeil du processus `noproc'. Sans effet si
 * le processus ne dort pas. */
void simu_wakeup (int noproc);

/* Renvoie la situation courante d'écoulement du temps. */
int simu_get_running (void);

/* Décide de l'écoulement du temps. */
void simu_set_running (int _runnning);

/* Inverse la situation courante d'écoulement du temps. */
void simu_swap_running (void);

/* Positionne la vitesse d'écoulement du temps. */
void simu_set_timespeed (int _timespeed);

/* Obtention de la vitesse d'écoulement du temps. */
int simu_get_timespeed (void);

/* Suspend l'écoulement du temps en sauvegardant la situation courante.
 * Plusieurs appels successifs à suspend_time sans alternance de
 * `resume_time' produisent un comportement non spécifié. */
void simu_suspend_time (void);
/* Restaure la situation de l'écoulement du temps avant le précédent
 * `suspend_time'. */
void simu_resume_time (void);

#endif
