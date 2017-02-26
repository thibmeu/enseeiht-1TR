/*******************************************************************************
 *  Auteur   : Xavier CRÉGUT
 *  Objectif : Définition des types Clef et Donnee
 ******************************************************************************/

#ifndef TYPES__H
#define TYPES__H

typedef char* Clef;
typedef int Donnee;
struct Couple
{
	Clef key;		// Fini par un '\0'
	Donnee value;	// Entier
};
typedef struct Couple Couple;

void init_Couple(Couple* this, Clef key, Donnee value);
/*
 * Procedure init_Couple(this: Couple out, key: Clef in, value: Donnee in)
 * 
 * Initialise un couple a partir d'une cle et d'une valeur
 * 
 * Necessite:
 * this != NULL
 * key et value valide
 * 
 * Assure:
 * Couple initialise aux valeurs fournies
 */

#endif
