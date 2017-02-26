#include "vector.h"
#include <stdlib.h>

Vector* create_expert(int size, int incr)
{
	Vector* v = malloc(sizeof(Vector));
	if (v)
	{
		v->t = malloc(size*sizeof(Vector));
		v->len = 0;
		v->trueLen = size;
		v->incr = incr;
	}
	return v;
}

Vector* create()
{
	return create_expert(10, 3);
}

void destroy(Vector** v)
{
	free(*v);
	*v = NULL;
}

int size(Vector v)
{
	return v.len;
}

int capacity(Vector v)
{
	return v.trueLen;
}

void add(Vector** v, int nNb)
{
	if ((*v)->len == (*v)->trueLen)
	{
		Vector* tmp = create_expert((*v)->len+(*v)->incr, (*v)->incr);
		for (int iNb = 0; iNb < (*v)->len; iNb++)
			add(&tmp, nNb);
		*v = tmp;
	}
	((*v)->t)[(*v)->len] = nNb;
	++(*v)->len;
}

int get(Vector v, int pNb)
{
	return (v.t)[pNb];
}


void set(Vector v, int pNb, int nNb)	
{
	(v.t)[pNb] = nNb;
}

void nRemove(Vector* v, int pNb)
{
	for (int iNb = pNb; iNb < v->len - 1; iNb++)
		(v->t)[iNb] = (v->t)[iNb+1];
	--v->len;
}

void adjust(Vector** v)
{
	Vector* tmp = create_expert((*v)->len, (*v)->incr);
	for (int iNb = 0; iNb < (*v)->len; iNb++)
		(tmp->t)[iNb] = ((*v)->t)[iNb];
	*v = tmp;
}

void insert(Vector** v, int pNb, int nNb)
{
	add(v, ((*v)->t)[(*v)->len]);
	for(int iNb = (*v)->len - 2; iNb > pNb; iNb--)
		((*v)->t)[iNb] = ((*v)->t)[iNb-1];
	((*v)->t)[pNb] = nNb;
}

void delete(Vector* v, int begin, int end)
{
	for (int iNb = end; iNb < v->len; iNb++)
		(v->t)[iNb] = (v->t)[iNb-begin];
	v->len -= end-begin;
}
