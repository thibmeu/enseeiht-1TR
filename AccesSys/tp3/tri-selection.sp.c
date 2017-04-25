#include "tri-selection.sp.h"
#include <assert.h>

int indice_min(Vecteur V, int i_debut, int i_fin) {
	/* l'indice du plus petit élément du tableau V compris entre les
	** indices i_debut et i_fin inclus.
	**
	** Nécessite
	**	i_debut et i_fin sont des indices valides de V
	*/

  assert(i_debut <= V.nb && i_fin <= V.nb);

  int Resultat, min, i;

  Resultat= i_debut;
  min= V.valeur[Resultat];
  for (i= i_debut+1; i<i_fin; i++) {
    if (V.valeur[i]<min) {
      Resultat= i;
      min= V.valeur[i];
    }
  }

  return Resultat;
}

void permuter(int *a, int *b) {
  /*   Échanger les valeurs des entiers a et b */

  int memoire; 

  memoire= *a;      
  *a= *b;
  *b= memoire;
}

void trier(Vecteur *V) {
  /* Trier le vecteur V contenant N éléments dans l'ordre croissant */

  int indice, imin;

  for (indice= 0; indice<V->nb; indice++) {
    imin= indice_min(*V, indice, V->nb);
    permuter(&(V->valeur[indice]), &(V->valeur[imin]));
  }

}
