/* Time-stamp: <02 Sep 2003 11:09 queinnec@enseeiht.fr> */

/* Copyright 2003 ENSEEIHT. */ 

/*
 * Implantation des sémaphores de Dijkstra avec les primivites Posix Threads.
 *
 * L'implantation est FIFO même si les mutex ou les variables conditions
 * des PThreads ne le sont pas (gestion explicite de la file d'attente).
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "semaphore.h"

 /* clé d'accès aux info_proc */
static pthread_key_t private_access;

/* Circular lists! */
/* Un processus peut être dans au plus une liste de sémaphores.
 * Chaque pthread possède une et exactement une structure info_proc,
 *  stockée dans son specific.
 */
typedef struct info_proc {
    pthread_cond_t private_cond; /* la vc du thread */
    int do_wakeup;               /* pour éviter les spurious wakeup */
    struct info_proc *next;
    struct info_proc *prev;
} info_proc;


struct semaphore {
    pthread_mutex_t protect;    /* protection d'accès */
    info_proc *en_attente;      /* liste des threads en attente */
    int compteur;               /* nb de jetons */
};

/****************************************************************/

/*
 * Ajout d'un élément à la fin de la liste.
 */
static void add (info_proc **l, info_proc *e)
{
    if (*l == NULL) {
        e->next = e;
        e->prev = e;
        *l = e;
    } else {
        e->next = *l;
        e->prev = (*l)->prev;
        (*l)->prev->next = e;
        (*l)->prev = e;
    }
}

/*
 * Extraction du premier élément de la liste.
 */
static info_proc *extract (info_proc **l)
{
    if (*l == NULL) {
        return NULL;
    } else {
        info_proc *hd = *l;
        if (hd->next == hd) {
            *l = NULL;
        } else {
            hd->next->prev = hd->prev;
            hd->prev->next = hd->next;
            *l = hd->next;
        }
        return hd;
    }
}

/*
 * Obtention (avec création si nécessaire) des infos privés du processus.
 */
static info_proc *get_info (void)
{
    info_proc *v;
    v = (info_proc *) pthread_getspecific (private_access);
    if (v == NULL) {
        v = malloc (sizeof (info_proc));
        pthread_cond_init (&(v->private_cond), NULL);
        v->do_wakeup = 0;
        v->next = NULL;
        v->prev = NULL;
        pthread_setspecific (private_access, v);
    }
    return v;
}

/****************************************************************/

void sem_P (semaphore_t s)
{
    pthread_mutex_lock (&(s->protect));
    if (s->compteur > 0) {      /* assez de jeton */
        (s->compteur)--;
    } else {                    /* pas assez => le processus se bloque */
        info_proc *self;
        self = get_info ();
       /* Ajoute self à la fin des entrants, */
        add (&(s->en_attente), self);
        self->do_wakeup = 0;
        while (! self->do_wakeup) {
            pthread_cond_wait (&(self->private_cond), &(s->protect));
        }
        /* Le débloqueur a donné le jeton. */
    }
    pthread_mutex_unlock (&(s->protect));
}

void sem_V (semaphore_t s)
{
    info_proc *p;
    pthread_mutex_lock (&(s->protect));
    p = extract (&(s->en_attente));
    if (p == NULL) {            /* personne en attente */
        (s->compteur)++;
    } else {                    /* transmet le jeton */
        p->do_wakeup = 1;
        pthread_cond_signal (&(p->private_cond));
    }
    pthread_mutex_unlock (&(s->protect));
}

/****************************************************************/

static void thread_terminaison (void *info)
{
    if (info != NULL) {
        /* Il faudrait vérifier que le thread n'utilise pas de sémaphore,
         * et n'est dans aucune des listes, mais pour cela, il faudrait
         * la liste des sémaphores, ou que chaque thread sache dans quel
         * sémaphore il est... */
        free (info);
    }
}

static pthread_once_t module_init_once = PTHREAD_ONCE_INIT;

static void module_init (void)
{
    pthread_key_create (&private_access, thread_terminaison);
}

semaphore_t sem_init (int val)
{
    semaphore_t s;

    pthread_once (&module_init_once, module_init);
    
    s = malloc (sizeof (struct semaphore));
    
    pthread_mutex_init (&(s->protect), NULL);
    s->compteur = val;
    s->en_attente = NULL;

    return s;
}


