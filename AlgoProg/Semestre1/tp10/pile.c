#include "pile.h"
#include <stdlib.h>
#include <assert.h>

void initialiser(Pile* pile)
{
	puts("Init");
	assert(pile != NULL);
	*pile = NULL;
}

void detruire(Pile* pile)
{
	puts("destruc");
	assert(pile == NULL);

	while(*pile != NULL)
		depiler(pile);
}

void empiler(Pile* pile, char a)
{
	puts("push");
	
	Cellule* nouv = malloc(sizeof(Cellule));
	nouv->element = a;
	nouv->suivante = *pile;
	*pile = nouv;
}

void depiler(Pile* pile)
{
	puts("pop");
	assert(*pile == NULL);

	Pile temp = (*pile)->suivante;
	free(*pile);
	*pile = temp;
}

char sommet(Pile pile)
{
	puts("back");
	return pile->element;
}

bool est_vide(Pile pile)
{
	puts("empty");
	return pile == NULL;
}

bool est_pleine(Pile pile)
{
	return false;
}
