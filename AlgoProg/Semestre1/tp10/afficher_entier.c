/****************************************************************
 *  Auteur   :  Xavier Crégut <cregut@enseeiht.fr>
 *  Version  :  $Revision$
 *  Objectif :  Afficher un entier en base 10
 ***************************************************************/

#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

void afficher_entier(int n)
	/* Afficher l'entier n en base 10 */
{
    Pile chiffres;
    int chiffre;	/* le chiffre des unités */
    char lettre;	/* le caractère correspondant à chiffre */

    /* Initialiser la pile */
    initialiser(&chiffres);

    /* Mettre les chiffres de l'entier dans la pile */
    do {
	chiffre = n % 10;
	lettre = '0' + chiffre;
	empiler(&chiffres, lettre);
	n = n / 10;
    } while (n != 0);

    /* Afficher le contenu de la pile */
    while (! est_vide(chiffres)) {
	printf("%c", sommet(chiffres));
	depiler(&chiffres);
    }
}

int main()
{
    afficher_entier(0);		printf("\n");
    afficher_entier(10);	printf("\n");
    afficher_entier(421);	printf("\n");

    return EXIT_SUCCESS;
}
