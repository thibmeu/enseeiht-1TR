/****************************************************************
 *  Auteur  :  Xavier Cr�gut <cregut@enseeiht.fr>
 *  Version :  $Revision$
 *  Objectif : V�rifier le parenth�sage d'une expression compos�e
 *		de parenth�ses et de crochets.
 ***************************************************************/

#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* v�rifier si l'expression est bien parenth�s�e (ok).  Dans
 * le cas, o� l'expression n'est pas bien parenth�s�e,
 * position_erreur contient l'indice du caract�re o� l'erreur
 * de parenth�sage a �t� d�tect�e.
 *
 * Remarque : un message est affich� � l'�cran si un
 * parenth�sage incorrect est trouv�.  Il serait pr�f�rable de
 * retourner un code d'erreur (type �num�r�) qui identifie
 * l'erreur d�tect�e.  L'utilisateur du sous-programme est
 * ensuite libre d'utiliser le code d'erreur comme il
 * l'entend, par exemple en affichant une explication.
 *
 * Assure
 *	! *ok ==> (*position_erreur >= 0)
 *			&& (*position_erreur <= length(expression));
 */
void verifier_parenthesage(const char expression[],
				bool *ok, int *position_erreur)
{
	Pile pile;
	initialiser(&pile);
	*ok = true;	

	for(*position_erreur = 0; ok && expression[*position_erreur] != '\0'; ++*position_erreur)
	{
		char curChar = expression[*position_erreur];
		switch (curChar)
		{
			case '(': case'[':
			{
				empiler(&pile, curChar);
				break;
			}
			case ')':
			{	
				if(est_vide(pile) || sommet(pile) != '(')
				{
					*ok = false;
					return;	
				}
				depiler(&pile);
				break;
			}
			case ']':
			{
				if(est_vide(pile) || sommet(pile) != '[')
				{
					*ok = false;
					return;
				}
				depiler(&pile);
				break;
			}
		}
	}
	*ok = est_vide(pile);
}

int main(int argv, char* argc[])
{
	bool ok;
	int position;
	
	char* test[9] = {
	"2*(x + y)", "occurrences[chr(ord(�0�) + (entiers[i] mod 4))]", "[ ( ( [ ] ) [ ( ) ( ) ] ) ]",
	"2*(x + y))", "occurrences[chr(ord(�0�)] + (entiers[i] mod 4))",
"[[[[", "]", "( ( ] )", "( [ ) ]"
	};
	for(int iString = 0; iString < 9; iString++)
	{
		verifier_parenthesage(test[iString], &ok, &position);
		printf("string : %s ok : %d, position : %d\n", test[iString], ok, position);
	}
	return 0;
}
