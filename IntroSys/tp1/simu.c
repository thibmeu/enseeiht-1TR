
#include <pthread.h>
#include <stdlib.h>
#include "simu.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define FALSE 0

typedef struct {
    int duree_sommeil;
    int do_wakeup;
    pthread_cond_t cond;
} simu_proc_t;

static simu_proc_t *simu_procs;

static pthread_mutex_t simu_mutex;

static int simu_nbprocs;

/* one system tick = 10ms */
/* one simulated tick = (1000/current_timespeed) system tick */
/* Dormir(n) = Dormir n simulated ticks. */

static int current_timespeed = 1;
static int system_ticks = 1;

/* Le temps s'écoule-t-il ou pas ? */
static int running = 1;

void simu_sleep (int noproc, int duree)
{
    pthread_mutex_lock (&simu_mutex);
    simu_procs[noproc].duree_sommeil = duree;
    simu_procs[noproc].do_wakeup = 0;
    while (! simu_procs[noproc].do_wakeup) {
        pthread_cond_wait (&(simu_procs[noproc].cond), &simu_mutex);
    }
    pthread_mutex_unlock (&simu_mutex);
}

/* Assume that simu_mutex is locked. */
static void simu_wakeup_internal (int noproc)
{
    simu_procs[noproc].do_wakeup = 1;
    pthread_cond_signal (&(simu_procs[noproc].cond));
}

void simu_wakeup (int noproc)
{
    pthread_mutex_lock (&simu_mutex);
    simu_wakeup_internal (noproc);
    pthread_mutex_unlock (&simu_mutex);
}

void ticker(int unused)
{    
  // printf("Je suis la\n");
  pthread_mutex_lock(&simu_mutex);
  //printf("puis la\n");
  if (running) {
    // printf("system_ticks=%d\n",system_ticks);
    if (system_ticks==0) {
      int i;
      for (i=0; i<simu_nbprocs; i++) {
	//printf("Proc : %d , duree_sommeil = %d\n",i,simu_procs[i].duree_sommeil);
	if (simu_procs[i].duree_sommeil==0) {
	
	  simu_wakeup_internal(i);
	}
	simu_procs[i].duree_sommeil--;
      }

      system_ticks = 1000/current_timespeed;
    }
    else {
      system_ticks --;
    }
    
    
  }
  pthread_mutex_unlock(&simu_mutex);
  signal(SIGALRM, ticker);
  alarm(1);
}
       

void simu_init (int nbprocs)
{
    int i;
    pthread_mutex_init (&simu_mutex, NULL);
    simu_nbprocs = nbprocs;
    simu_set_timespeed (500);
    simu_procs = malloc (nbprocs * sizeof (simu_proc_t));
    for (i = 0; i < nbprocs; i++) {
        pthread_cond_init (&(simu_procs[i].cond), NULL);
        simu_procs[i].duree_sommeil = -1;
    }
    //printf("Je suis ici !\n");
    signal(SIGALRM, ticker);
    alarm(1);
 
}

int simu_get_running (void)
{
    int res;
    pthread_mutex_lock (&simu_mutex);
    res = running;
    pthread_mutex_unlock (&simu_mutex);
    return res;
}

void simu_set_running (int _running)
{
    pthread_mutex_lock (&simu_mutex);
    running = _running;
    pthread_mutex_unlock (&simu_mutex);
}

void simu_swap_running (void)
{
    pthread_mutex_lock (&simu_mutex);
    running = !running;
    pthread_mutex_unlock (&simu_mutex);
}

void simu_set_timespeed (int _timespeed)
{
    pthread_mutex_lock (&simu_mutex);
    current_timespeed = _timespeed;
    system_ticks = 1000 / current_timespeed;
    pthread_mutex_unlock (&simu_mutex);
}

int simu_get_timespeed (void)
{
    int res;
    pthread_mutex_lock (&simu_mutex);
    res = current_timespeed;
    pthread_mutex_unlock (&simu_mutex);
    return res;
}

static int previous_running;

void simu_suspend_time (void)
{
    pthread_mutex_lock (&simu_mutex);
    previous_running = running;
    running = FALSE;
    pthread_mutex_unlock (&simu_mutex);
}

void simu_resume_time (void)
{
    pthread_mutex_lock (&simu_mutex);
    running = previous_running;
    pthread_mutex_unlock (&simu_mutex);
}

