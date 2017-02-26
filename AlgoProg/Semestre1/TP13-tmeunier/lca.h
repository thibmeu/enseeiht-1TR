/*******************************************************************************
 *  Auteur  : Xavier CRÉGUT <nom@n7.fr>
 *  Objectif :
 *	Spécification d'une LCA, structure de données associative
 ******************************************************************************/

#ifndef LCA__H
#define LCA__H

#include <stdbool.h>
#include "types.h"
#include "lca-specifique.h"
#include "lca-solo.h"
#define MAX_KEY 1000

// TODO: Donner la spécification des sous-programmes dont la spécification est la même
// pour LCA et TH.

bool empty_LCA(LCA this);
/*
 * Fonction empty_LCA(this: LCA in)
 * 
 * Indique si une LCA est vide ou non
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * Renvoie Vrai si la LCA est vide, Faux sinon
 */

void add_LCA(LCA* this, Clef key, Donnee value);
/*
 * Proedure add_LCA(this: LCA in/out, key: Clef in, value: Donnee in)
 * 
 * Ajoute dans une LCA une donnee en precisant sa clef
 * Si la clef est dejà utilisee, la nouvelle donnee remplace la donnee precedemment associee à cette clef
 * 
 * Necessite:
 * this != NULL
 * key et value valide
 * 
 * Assure:
 * L'ajout se fait selon l'ordre alphabetique
 */

void delete_LCA(LCA* this, Clef key);
/*
 * Procedure  delete_LCA(this: LCA in/out, key: Clef in)
 * 
 * Supprimer d’une LCA la donnee associee à une clef
 * Si la clef n’est pas utilisee dans la LCA, la LCA n’est pas modifiee
 * 
 * Necessite:
 * this != NULL
 * key valide
 * 
 * Assure:
 * L'element est supprime si possible
 */

bool has_key_LCA(LCA this, Clef key);
/*
 * Fonction has_key_LCA(this: LCA in, key: Clef in)
 * 
 * Indique si une clef est utilisee dans une LCA
 * 
 * Necessite:
 * this et key valide
 * 
 * Assure:
 * Renvoie Vrai si la clef est dans la LCA, Faux sinon
 */

Donnee getValue_LCA(LCA this, Clef key);
/*
 * Procedure getValue_LCA(this: LCA in, key: Clef in)
 * 
 * Recupere la donnee associee à une clef
 * 
 * Necessite:
 * this et key valide
 * key dans la LCA
 * 
 * Assure:
 * Renvoie une Donnee
 */

void clear_LCA(LCA* this);
/*
 * Procedure clear_LCA(this: LCA in/out)
 * 
 * Supprime toutes les donnees que contient la LCA
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * LCA vide
 */

void destroy_LCA(LCA* this);
/*
 * Procedure destroy_LCA(this: LCA in/out)
 * 
 * Libere toutes les ressources qu’utilise la LCA
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * LCA desallouee
 * *this = NULL
 */

void print_LCA(LCA this);
/*
 * Procedure print_LCA(this: LCA in)
 * 
 * Affiche tous les couples (clef, donnee) enregistres dans la LCA
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * L'affichage se fait sur la stdout
 */

#endif
