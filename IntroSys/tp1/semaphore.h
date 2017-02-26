/* Time-stamp: <02 Sep 2003 11:09 queinnec@enseeiht.fr> */
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

/* Un s�maphore est un pointeur sur une structure priv�e,
 * implant�e dans semaphore.c */
typedef struct semaphore *semaphore_t;

semaphore_t sem_init (int val);
void sem_P (semaphore_t s);
void sem_V (semaphore_t s);

#endif /* _SEMAPHORE_H_ */
