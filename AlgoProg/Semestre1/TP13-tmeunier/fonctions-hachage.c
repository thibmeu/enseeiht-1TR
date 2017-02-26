/*******************************************************************************
 *  Auteur   : Thibault MEUNIER
 *  Objectif : Implantation du module fonctions-hachages.
 ******************************************************************************/

#include "fonctions-hachage.h"
#include <string.h>

size_t taille(const char* str)
{
	return strlen(str);
}

size_t initiale(const char* str)
{
	return (size_t)(*str);
}

size_t somme(const char* str)
{
	size_t res = 0, iChar = 0;
	while(*(str+iChar) != '\0')
	{
		res += (size_t)(*(str+iChar));
		iChar++;
	}
	return res;
}

size_t java(const char* str)
{
	size_t res = 0, iChar = 0;
	while(*(str+iChar) != '\0')
	{
		res *= 31;
		res += (size_t)(*(str+iChar));
		iChar++;
	}
	return res;
}
