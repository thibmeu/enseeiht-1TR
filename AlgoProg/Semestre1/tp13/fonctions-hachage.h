/*******************************************************************************
 *  Auteur   : 
 *  Objectif : Quelques fonctions de hachages
 ******************************************************************************/

#ifndef FONCTIONS_HACHAGE__H
#define FONCTIONS_HACHAGE__H
#include <stddef.h>
#define NB_HASH_FUNCTIONS 4




size_t taille(const char* str);
/*
 * Fonction taille(str: Chaine de Caracteres in)
 * 
 * Renvoie la taille d'une chaine de caracteres
 * 
 * Necessite:
 * str != NULL
 * str se terminant par '\0'
 * 
 * Assure:
 * Renvoie un entier non signe
 */

size_t initiale(const char* str);
/*
 * Fonction initiale(str: Chaine de Caracteres in)
 * 
 * Renvoie la valeur de l'initiale d'une chaine de caractere
 * 
 * Necessite:
 * str != NULL
 * str se terminant par '\0'
 * 
 * Assure:
 * Renvoie un entier non signe
 */

size_t somme(const char* str);
/*
 * Fonction somme(str: Chaine de Caracteres in)
 * 
 * Renvoie la somme des valeurs des caracteres d'une chaine de caracteres
 * 
 * Necessite:
 * str != NULL
 * str se terminant par '\0'
 * 
 * Assure:
 * Renvoie un entier non signe
 */

size_t java(const char* str);
/*
 * Fonction java(str: Chaine de Caracteres in)
 * 
 * Renvoie la valeur de hasha la maniere de java
 * 
 * Necessite:
 * str != NULL
 * str se terminant par '\0'
 * Chaine pas trop grande(ou alors des modulos)
 * 
 * Assure:
 * Renvoie un entier non signe
 */

#endif
