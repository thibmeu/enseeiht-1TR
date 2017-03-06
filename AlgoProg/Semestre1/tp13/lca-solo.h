#include "lca-specifique.h"

void add_LCA_solo(LCA* this, Clef key, Donnee value);
/*
 * Procedure add_LCA_solo(this: LCA in/out, key: Clef in, value: Donnee in)
 * 
 * Ajoute une nouvelle cellule a la tete de la LCA
 * 
 * Necessite:
 * this != NULL
 * key et value correctement initialises
 * 
 * Assure:
 * Une nouvelle cellule est insere en debut de LCA
 * this->next_nouveau = this_ancien
 */

void delete_LCA_solo(LCA* this);
/*
 * Procedure delete_LCA_solo(this: LCA in/out)
 * 
 * Supprime la cellule en tete de LCA
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * this_nouveau = this->next_ancien
 */

