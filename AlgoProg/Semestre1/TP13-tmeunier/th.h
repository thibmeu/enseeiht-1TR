/*******************************************************************************
 *  Auteur  : Xavier CRÉGUT <nom@n7.fr>
 *  Objectif :
 *	Spécification d'une TH, structure de données associative
 ******************************************************************************/

#ifndef TH__H
#define TH__H

#include <stdbool.h>
#include "types.h"
#include "th-specifique.h"
#include "lca-solo.h"
#define MAX_KEY 1000

// TODO: Donner la spécification des sous-programmes dont la spécification est la même
// pour LCA et TH.

bool empty_TH(TH this);
/*
 * Fonction empty_TH(this: TH in)
 * 
 * Indique si une TH est vide ou non
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * Renvoie Vrai si la TH est vide, Faux sinon
 */

void add_TH(TH* this, Clef key, Donnee value);
/*
 * Proedure add_TH(this: TH in/out, key: Clef in, value: Donnee in)
 * 
 * Ajoute dans une TH une donnee en precisant sa clef
 * Si la clef est dejà utilisee, la nouvelle donnee remplace la donnee precedemment associee à cette clef
 * 
 * Necessite:
 * this != NULL
 * key et value valide
 * 
 * Assure:
 * L'ajout se fait selon l'ordre alphabetique
 */

void delete_TH(TH* this, Clef key);
/*
 * Procedure  delete_TH(this: TH in/out, key: Clef in)
 * 
 * Supprimer d’une TH la donnee associee à une clef
 * Si la clef n’est pas utilisee dans la TH, la TH n’est pas modifiee
 * 
 * Necessite:
 * this != NULL
 * key valide
 * 
 * Assure:
 * L'element est supprime si possible
 */

bool has_key_TH(TH this, Clef key);
/*
 * Fonction has_key_TH(this: TH in, key: Clef in)
 * 
 * Indique si une clef est utilisee dans une TH
 * 
 * Necessite:
 * this et key valide
 * 
 * Assure:
 * Renvoie Vrai si la clef est dans la TH, Faux sinon
 */

Donnee getValue_TH(TH this, Clef key);
/*
 * Procedure getValue_TH(this: TH in, key: Clef in)
 * 
 * Recupere la donnee associee à une clef
 * 
 * Necessite:
 * this et key valide
 * key dans la TH
 * 
 * Assure:
 * Renvoie une Donnee
 */

void clear_TH(TH* this);
/*
 * Procedure clear_TH(this: TH in/out)
 * 
 * Supprime toutes les donnees que contient la TH
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * TH vide
 */

void destroy_TH(TH* this);
/*
 * Procedure destroy_TH(this: TH in/out)
 * 
 * Libere toutes les ressources qu’utilise la TH
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * TH desallouee
 * *this = NULL
 */

void print_TH(TH this);
/*
 * Procedure print_TH(this: TH in)
 * 
 * Affiche tous les couples (clef, donnee) enregistres dans la TH
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * L'affichage se fait sur la stdout
 */

#endif
