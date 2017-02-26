/****************************************************************
 *  Auteur  : Xavier CRÉGUT
 *  Objectif : Implantation d'une pile de char
 ***************************************************************/

#include <assert.h>
#include <stdlib.h>
#include "pile.h"

void initialiser(Pile *p)
{
    assert(p != NULL);

    p->nb = 0;

    assert(est_vide(*p));
}

char sommet(Pile p)
{
    assert(!est_vide(p));
	return *(p.elements+p.nb-1);
}

void depiler(Pile *p)
{
    assert(p != NULL);
    assert(!est_vide(*p));
	--p->nb;
}

void empiler(Pile *p, char v)
{
    assert(p != NULL);
    assert(!est_pleine(*p));

	*(p->elements+p->nb) = v;
	++p->nb;
    assert(sommet(*p) == v);
}

bool est_vide(Pile p)
{
	return p.nb == 0;
}

bool est_pleine(Pile p)
{
	return p.nb == PILE_CAPACITE;
}
