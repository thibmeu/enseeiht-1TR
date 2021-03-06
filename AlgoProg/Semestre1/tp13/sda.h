/*******************************************************************************
 *  Auteur  : Xavier CRÉGUT <nom@n7.fr>
 *  Objectif :
 *	Spécification d'une SDA, structure de données associative
 ******************************************************************************/

#ifndef SDA__H
#define SDA__H

#include <stdbool.h>
#include "types.h"
#include "sda-specifique.h"
#include "lca-solo.h"
#define MAX_KEY 1000

// TODO: Donner la spécification des sous-programmes dont la spécification est la même
// pour LCA et TH.

bool empty_SDA(SDA this);
/*
 * Fonction empty_SDA(this: SDA in)
 * 
 * Indique si une SDA est vide ou non
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * Renvoie Vrai si la SDA est vide, Faux sinon
 */

void add_SDA(SDA* this, Clef key, Donnee value);
/*
 * Proedure add_SDA(this: SDA in/out, key: Clef in, value: Donnee in)
 * 
 * Ajoute dans une SDA une donnee en precisant sa clef
 * Si la clef est dejà utilisee, la nouvelle donnee remplace la donnee precedemment associee à cette clef
 * 
 * Necessite:
 * this != NULL
 * key et value valide
 * 
 * Assure:
 * L'ajout se fait selon l'ordre alphabetique
 */

void delete_SDA(SDA* this, Clef key);
/*
 * Procedure  delete_SDA(this: SDA in/out, key: Clef in)
 * 
 * Supprimer d’une SDA la donnee associee à une clef
 * Si la clef n’est pas utilisee dans la SDA, la SDA n’est pas modifiee
 * 
 * Necessite:
 * this != NULL
 * key valide
 * 
 * Assure:
 * L'element est supprime si possible
 */

bool has_key_SDA(SDA this, Clef key);
/*
 * Fonction has_key_SDA(this: SDA in, key: Clef in)
 * 
 * Indique si une clef est utilisee dans une SDA
 * 
 * Necessite:
 * this et key valide
 * 
 * Assure:
 * Renvoie Vrai si la clef est dans la SDA, Faux sinon
 */

Donnee getValue_SDA(SDA this, Clef key);
/*
 * Procedure getValue_SDA(this: SDA in, key: Clef in)
 * 
 * Recupere la donnee associee à une clef
 * 
 * Necessite:
 * this et key valide
 * key dans la SDA
 * 
 * Assure:
 * Renvoie une Donnee
 */

void clear_SDA(SDA* this);
/*
 * Procedure clear_SDA(this: SDA in/out)
 * 
 * Supprime toutes les donnees que contient la SDA
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * SDA vide
 */

void destroy_SDA(SDA* this);
/*
 * Procedure destroy_SDA(this: SDA in/out)
 * 
 * Libere toutes les ressources qu’utilise la SDA
 * 
 * Necessite:
 * this != NULL
 * 
 * Assure:
 * SDA desallouee
 * *this = NULL
 */

void print_SDA(SDA this);
/*
 * Procedure print_SDA(this: SDA in)
 * 
 * Affiche tous les couples (clef, donnee) enregistres dans la SDA
 * 
 * Necessite:
 * this initialise
 * 
 * Assure:
 * L'affichage se fait sur la stdout
 */

#endif
