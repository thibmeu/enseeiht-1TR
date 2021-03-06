#ifndef TH_SPECIFIQUE_H
#define TH_SPECIFIQUE_H
#include <stdlib.h>

// TODO: Donner la définition du type TH (et autres types nécessaires).
#include "types.h"
#include "lca.h"

struct TH
{
	LCA* table;
	size_t size;
	size_t (*hash_function)(const char*);
};
typedef struct TH* TH;	//Necessaire pour que le type abstrait SDA soit homogene

// TODO: Donner la spécification des sous-programmes dont la signature est
// spécifique à TH.

void init_TH(TH* this, size_t size, size_t (*hash_function)(const char*));
/*
 * Procedure init_TH(this: TH out, size: Taille in, hash_function: Taille Fonction(Chaine de Caracteres in) in)
 * 
 * Initialise une TH vide
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * LCA initialise et vide
 */

#endif
