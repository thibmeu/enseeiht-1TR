#ifndef PILE_H
#define PILE_H
#include <stdio.h>
#include <stdbool.h>

struct Cellule
{
	char element;
	struct Cellule* suivante;
};
typedef struct Cellule Cellule;
typedef Cellule* Pile;

void initialiser(Pile* pile);

void detruire(Pile* pile);

void empiler(Pile* pile, char a);

void depiler(Pile* pile);

char sommet(Pile pile);

bool est_vide(Pile pile);

bool est_pleine(Pile pile);

#endif
