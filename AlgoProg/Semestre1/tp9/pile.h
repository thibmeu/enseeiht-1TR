/****************************************************************
 *  Auteur  : Xavier CRÉGUT
 *  Objectif : Définition d'une pile de char
 ***************************************************************/

#ifndef PILE__H	/* protéger contre la double inclusion */
#define PILE__H

#include <stdbool.h>

#define PILE_CAPACITE 10		/* Taille de la pile */

struct Pile {
    char elements[PILE_CAPACITE];	/* Les éléments empilés */
    int nb;		/* Nombre d'éléments empilés */
};
typedef struct Pile Pile;

void initialiser(Pile *p);
	/* Initialiser la pile.  La pile est vide.
	 *
	 * Nécessite :
	 *	p != NULL;
	 *
	 * Assure :
	 *	est_vide(*p);
	 */

char sommet(Pile p);
	/* L'élément au sommet de la pile p.
	 *
	 * Nécessite :
	 *	! est_vide(p);
	 */

void depiler(Pile *p);
	/* Supprimer l'élément au sommet de la pile p.
	 *
	 * Nécessite :
	 *	p != NULL;
	 *	! est_vide(*p);
	 */

void empiler(Pile *p, char v);
	/* Ajouter l'élément v en sommet de pile p.
	 *
	 * Nécessite :
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
