/****************************************************************
 *  Auteur  : Xavier CR�GUT
 *  Objectif : D�finition d'une pile de char
 ***************************************************************/

#ifndef PILE__H	/* prot�ger contre la double inclusion */
#define PILE__H

#include <stdbool.h>

#define PILE_CAPACITE 10		/* Taille de la pile */

struct Pile {
    char elements[PILE_CAPACITE];	/* Les �l�ments empil�s */
    int nb;		/* Nombre d'�l�ments empil�s */
};
typedef struct Pile Pile;

void initialiser(Pile *p);
	/* Initialiser la pile.  La pile est vide.
	 *
	 * N�cessite :
	 *	p != NULL;
	 *
	 * Assure :
	 *	est_vide(*p);
	 */

char sommet(Pile p);
	/* L'�l�ment au sommet de la pile p.
	 *
	 * N�cessite :
	 *	! est_vide(p);
	 */

void depiler(Pile *p);
	/* Supprimer l'�l�ment au sommet de la pile p.
	 *
	 * N�cessite :
	 *	p != NULL;
	 *	! est_vide(*p);
	 */

void empiler(Pile *p, char v);
	/* Ajouter l'�l�ment v en sommet de pile p.
	 *
	 * N�cessite :
	 *	p != NULL;
	 *	! est_pleine(*p);
	 *
	 * Assure :
	 *	sommet(*p) == v;
	 */

bool est_vide(Pile p);
	/* la pile est-elle vide ?  */

bool est_pleine(Pile p);
	/* la pile est-elle pleine ?  */

#endif
