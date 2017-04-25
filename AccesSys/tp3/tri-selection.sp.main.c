/*******************************************************************************
**  Auteur :  Jérôme ERMONT
**  Date :    10/02/2011, 17:31:22
**
**  Objectif :
**	Implanter un algorithme de tri par sélection (en utilisant des
**	sous-programmes)
*******************************************************************************/

#include "tab-lecture-ecriture.h"
#include "tri-selection.sp.h"

#include <stdio.h>
#include <stdlib.h>
#define CAPACITE 100

int main() {

  /* Trier un tableau en utilisant le principe du tri par sélection */

  Vecteur mon_tableau;
  
  initialiser(&mon_tableau, CAPACITE);
  saisir(&mon_tableau);
  trier(&mon_tableau);

  afficher(mon_tableau);
  printf("\n");

  liberer(&mon_tableau);

}
  
/* Tests effectués :

-1			=> []
0 -1			=> [0]
1 2 3 -1		=> [1, 2, 3]
3 2 1 -1		=> [1, 2, 3]
1 2 3 4 5 6 7 8 9 10 -1	=> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
1 2 3 4 5 6 7 8 9 10 11 -1 => [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
1 2 3 1 2 3 12 3 -1	=> [1, 1, 2, 2, 3, 3, 3, 12]

*/
