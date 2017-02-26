/****************************************************************************/
/* Scheduling of a list of periodic tasks following first come first served */
/****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>

/* Length of the scheduling sequence */
int MAX_CYCLES=0;
/* Current step of scheduling */
int cycle=0;

/* Structure for a periodic task */
struct periodic_task
{
  int id_task; /* Identifier or the task */
  int t0; /* First wake up */
  int C; /* WCET */
  int P; /* Period */
};

/* Structure for a list of pending periodic tasks */
struct list_periodic_tasks
{
  struct periodic_task task;
  struct list_periodic_tasks *next;
};

/* The table of periodic tasks */
struct periodic_task *ttasks;

/* The table of periodic tasks */
struct periodic_task *atasks;

/* Number of tasks in the table */
int nb_tasks;

/* The list of pending periodic tasks */
struct list_periodic_tasks *ltasks;

/****************************************************************************/
/* Add a task to the list of pending periodic tasks                         */
/****************************************************************************/
struct list_periodic_tasks *add_task(struct periodic_task task,
				     struct list_periodic_tasks *l)
{
  struct list_periodic_tasks *laux, *laux2;

  laux=(struct list_periodic_tasks *) malloc
    (sizeof(struct list_periodic_tasks));
  if (laux==NULL)
     {
       perror("Error ! entry not created in task list");
       exit(1);
     }
  /* Initialize the new pending task */
  (laux->task).id_task=task.id_task;
  (laux->task).t0=task.t0;
  (laux->task).C=task.C;
  (laux->task).P=task.P;
  laux->next = NULL;
  /* Insert the new task at the end of the list */
  if (l==NULL)
    l=laux;
  else
    {
      laux2=l;
      while (laux2->next!=NULL && laux2->next->task.P < task.P)
	    laux2=laux2->next;

      if (laux2->next != NULL)
          laux->next = laux2->next;
      laux2->next=laux;
    }

  return l;
}

/****************************************************************************/
/* Remove finished task from the list of pending tasks                     */
/****************************************************************************/
struct list_periodic_tasks *update_tasks(struct list_periodic_tasks *l)
{
  struct list_periodic_tasks *l_aux,*l_aux2;

  if (l!=NULL)
    {
      if ((l->task).C==0)
	l=l->next;
      else
	{
	  l_aux=l->next;
	  l_aux2=l;
	  
	  while (l_aux!=NULL)
	    {
	      if (((l_aux->task).C)==0)
		l_aux2->next=l_aux->next;
	      l_aux=l_aux->next;
	      l_aux2=l_aux2->next;
	    }
	}
    }
  
  return l;
}

/****************************************************************************/
/* One step of scheduling of the tasks                                      */
/****************************************************************************/
void scheduling(struct list_periodic_tasks *l)
{

  /* The first task of the list is executed (nothing if the list is empty */
  if (l!=NULL)
    {
      printf("Cycle %d, task %d is executed \n",cycle,(l->task).id_task);
      (l->task).C--;
    }
  else
    printf("Cycle %d, processor inactive\n",cycle);
}

/****************************************************************************/
/* Schedulability test for Rate Monotonic                                   */
/****************************************************************************/
int schedulability_test()
{
  int i;
  double sum=0.0;
  double criteria;

  for (i=0; i<nb_tasks; i++)
    sum+=((double)(ttasks[i].C))/((double)(ttasks[i].P));

  printf("sum : %lf\n",sum);

  criteria=((double) nb_tasks)*(pow(2.0,1.0/(double) nb_tasks)-1.0);


  printf("criteria : %lf\n",criteria);
  if (sum<=criteria)
    {
      printf("Schedulability test : satisfied\n");
      return(1);
    }
  else
    {
      printf("Schedulability test : not satisfied\n");
      return(2);
    }

}

/****************************************************************************/
/* Show the characteristics of the tasks                                    */
/****************************************************************************/
void show_tasks ()
{
  int i;

  printf ("\n\n");
  for (i=0;i<nb_tasks;i++)
    printf ("Task %d: first wake up %d, WCET %d, period %d\n",
	    ttasks[i].id_task, ttasks[i].t0, ttasks[i].C, ttasks[i].P);
}

/****************************************************************************/
/* Show the characteristics of the pending tasks                            */
/****************************************************************************/
void show_pending (struct list_periodic_tasks *l)
{
  while (l!=NULL)
    {
      printf ("Task %d: first wake up %d, WCET %d, period %d\n",
	      (l->task).id_task, (l->task).t0, (l->task).C, (l->task).P);
      l=l->next;
    }
}

/****************************************************************************/
/* Main program                                                             */
/****************************************************************************/
int main()
{
  int i;

  fflush(stdin);
  printf ("Number of tasks : "); scanf("%d",&nb_tasks);

  /* Memory allocation of the table of tasks */
  ttasks=(struct periodic_task *) calloc
    (nb_tasks, sizeof(struct periodic_task));
  if (ttasks==NULL)
    {
      perror("Error ! Table of tasks not allocated !");
      exit(1);
    }
 
  /* Read the tasks */
   for (i=0;i<nb_tasks;i++)
    {
      printf("\nCharacteristics of task %d\n",i+1);
      ttasks[i].id_task=i+1;
      printf("First wake up : "); scanf("%d",&ttasks[i].t0);
      printf("WCET : "); scanf("%d",&ttasks[i].C);
      printf("Period : "); scanf("%d",&ttasks[i].P);
      
     if (MAX_CYCLES<ttasks[i].P)
       MAX_CYCLES=ttasks[i].P;
    }
   show_tasks ();

   /* schedulability_test();*/

   ltasks=NULL;

   /* Scheduling for two times the longest period */
   MAX_CYCLES=MAX_CYCLES*2;
   
   for (cycle=0;cycle<MAX_CYCLES;cycle++)
     {
       /* Insert tasks which wake up in the list of pending tasks */
       for (i=0; i<nb_tasks; i++)
	 if (ttasks[i].t0==(cycle % ttasks[i].P))
	   ltasks=add_task(ttasks[i],ltasks);
       /* One step of scheduling */
       scheduling(ltasks);
       
       /* Remove finished tasks from pending tasks*/
       ltasks=update_tasks(ltasks);
     }
   
   return(0);
}
