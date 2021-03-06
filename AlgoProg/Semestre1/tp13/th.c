/*******************************************************************************
 *  Auteur   : 
 *  Objectif : Implantation de la table de hachage
 ******************************************************************************/

#include "th.h"
#include <stdio.h>
#include <stdlib.h>

void init_TH(TH* this, size_t size, size_t (*hash_function)(const char*))
{
	*this = malloc(sizeof(struct TH));
	(*this)->table = malloc(size* sizeof(LCA));
	for(int iLCA = 0; iLCA < size; iLCA++)
		init_LCA(((*this)->table + iLCA));
	(*this)->size = size;
	(*this)->hash_function = hash_function;
}

bool empty_TH(TH this)
{
	bool res = true;
	for (int iLCA = 0; iLCA < this->size; iLCA++)
		res = res && empty_LCA(*(this->table + iLCA));
	return res;
}

void add_TH(TH* this, Clef key, Donnee value)
{
	size_t hash = ((*this)->hash_function)(key)%((*this)->size);
	add_LCA((*this)->table+hash, key, value);
}

void delete_TH(TH* this, Clef key)
{
	size_t hash = ((*this)->hash_function)(key)%((*this)->size);
	delete_LCA((*this)->table+hash, key);
}

bool has_key_TH(TH this, Clef key)
{
	size_t hash = (this->hash_function)(key)%(this->size);
	return has_key_LCA(*(this->table + hash), key);
}

Donnee getValue_TH(TH this, Clef key)
{
	size_t hash = (this->hash_function)(key)%(this->size);
	return getValue_LCA(*(this->table+hash), key);
}

void clear_TH(TH* this)
{
	for (int iLCA = 0; iLCA < (*this)->size; iLCA++)
		clear_LCA((*this)->table + iLCA);
}

void destroy_TH(TH* this)
{
	clear_TH(this);
	free(*this);
	*this = NULL;
}

void print_TH(TH this)
{
	for (int iLCA = 0; iLCA < this->size; iLCA++)
	{
		printf("% 3d[@-]", iLCA);
		print_LCA(*(this->table + iLCA));
	}
}
