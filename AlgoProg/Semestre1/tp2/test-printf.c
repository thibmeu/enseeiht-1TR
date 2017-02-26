/**********************************************************************
 *  Auteur   : Xavier Crégut <prenom.nom@enseeiht.fr>
 *  Version  : 1.4
 *  Objectif : Programme pour comprendre :
 *	- les limites de printf
 *	- l'intérêt du compilateur et des messages d'avertissement !
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LG_FORMAT	20	/* longueur maximale d'un format */

int main()
{
    char c1 = '1', c2 = '2', c3 = '3';	/* trois caractères */

    /* Afficher c2 seul */
    printf("c2 = %c\n", c2);
    printf("c2 = %i\n", c2);

    /* Afficher c1, c2 et c3 */
    printf("c1c2c3 = %c%c%c\n",    c1, c2, c3);
    printf("c1c2c3 = %i%i%i\n",    c1, c2, c3);
    printf("c1c2c3 = %li%li%li\n", (long int) c1, (long int) c2, (long int) c3);
    printf("c1c2c3 = %s%s%s\n",    &c1, &c2, &c3);

    /* Afficher avec un format défini par l'utilisateur du programme */
    {
	char format[LG_FORMAT+1];
		/* format saisi par l'utilisateur, donc inconnu du
		 * compilateur.
		 */

	/* saisir le format */
	printf("Donner un format : ");
	fgets(format, LG_FORMAT, stdin);
	    /* Remarque : le retour à la ligne de la saisie est
	     * dans le format.  */

	/* afficher le format pour vérification */
	printf("Le format saisi est : %s", format);

	/* afficher avec le format saisi */
	printf(format, c1, c2, c3);
    }

    return EXIT_SUCCESS;
}
