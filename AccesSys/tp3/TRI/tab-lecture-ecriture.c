#include "tab-lecture-ecriture.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void afficher(Vecteur tab) {
	/* afficher le tableau tab contenant nb éléments
	**
	** Nécessite :
	**	tab.nb >= 0		-- nb d'éléments cohérent
	*/
  int i;

  assert(tab.nb >= 0);

  if (tab.nb == 0) 
    printf("[]");
  else {
    printf("[%d", tab.valeur[0]);
    for (i= 1; i<tab.nb; i++) 
      printf(", %d", tab.valeur[i]);
    printf("]");
  }

}

void saisir(Vecteur *tab) {
	/* remplir le tableau tab de capacité max avec des entiers lus au
	** clavier.  nb est le nombre d'éléments effectivement lus.
	**
	** Nécessite :
	**	max > 0		-- max strictement positif
	**
	** Assure:
	**	0 <= nb <= max	-- nb d'entiers lus cohérent
	**
	** Principe : On demande à l'utilisateur les valeurs à ranger dans le
	** tableau.  On arrête la saisie sur une valeur strictement négative.
	*/

  assert(tab->max > 0);
  assert(0 <= tab->nb && tab->nb <= tab->max);

  int valeur;
  
  scanf("%d", &valeur);
  while ((valeur >= 0) && (tab->nb < tab->max)) {
    tab->valeur[tab->nb]= valeur;
    tab->nb++;
    scanf("%d", &valeur);
  }

  if (valeur >= 0) {
    printf("Attention : la saisie a ete tronquee car la capacite du tableau est %d\n", tab->max);
  }

}

void initialiser(Vecteur *tab, int CAPACITE) {
	/* initialiser un tableau tab de capacité CAPACITE
	**
	** Nécessite :
	**	CAPACITE > 0		-- CAPACITE strictement positif
	**
	*/
  assert(CAPACITE > 0);
  
  tab->max= CAPACITE;
  tab->nb= 0;
  tab->valeur= malloc(CAPACITE*sizeof(int));
}
  
void liberer(Vecteur *tab) {
  /* Libère la mémoire utilisée par le tableau tab */
  tab->max= 0;
  tab->nb= 0;
  free(tab->valeur);
}
