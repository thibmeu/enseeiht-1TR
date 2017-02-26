#ifndef TAB_LECTURE_ECRITURE__H
#define TAB_LECTURE_ECRITURE__H

typedef struct {
  int max;
  int nb;
  int *valeur;
} Vecteur;

void afficher(Vecteur tab);

void saisir(Vecteur *tab);

void initialiser(Vecteur *tab, int CAPACITE);

void liberer(Vecteur *tab);
#endif
