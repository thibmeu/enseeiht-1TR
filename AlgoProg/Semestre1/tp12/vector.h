#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

struct Vector
{
	int* t;		//Donnees
	int len;	//Nombre de donnees
	int trueLen;	//Capacite maximale
	int incr;	//Increment
};
typedef struct Vector Vector;

Vector* create_expert(int size, int incr);
/*
Cree un vector de capacite size et d'increment incr

Necessite:
size > 0
incr > 0

Assure:
Le vecteur est vide
*/

Vector* create();

void destroy(Vector** v);

int size(Vector v);

int capacity(Vector v);

void add(Vector** v, int nNb);

int get(Vector v, int pNb);

void set(Vector v, int pNb, int nNb);

void nRemove(Vector* v, int pNb);

void adjust(Vector** v);

void insert(Vector** v, int pNb, int nNb);

void delete(Vector* v, int begin, int end);

#endif
