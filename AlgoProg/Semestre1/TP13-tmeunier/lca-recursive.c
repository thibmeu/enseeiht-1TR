/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Implantation de la LCA
 ******************************************************************************/

#include "lca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_LCA(LCA* this)
{
	*this = NULL;
}

bool empty_LCA(LCA this)
{
	return this == NULL;
}

void add_LCA(LCA* this, Clef key, Donnee value)
{
	if(*this == NULL || strcmp(key, (*this)->couple.key) < 0)
		add_LCA_solo(this, key, value);
	else
	{
		if(strcmp(key, (*this)->couple.key) == 0)
			(*this)->couple.value = value;
		else if((*this)->next == NULL || strcmp(key, (*this)->next->couple.key) < 0)
			add_LCA_solo(&((*this)->next), key, value);
		else if (strcmp(key, (*this)->next->couple.key) == 0)
			(*this)->next->couple.value = value;
		else
			add_LCA(&((*this)->next), key, value);
	}
}

void delete_LCA(LCA* this, Clef key)
{
	if (*this != NULL)
	{	
		if(strcmp(key, (*this)->couple.key) == 0)
			delete_LCA_solo(this);
		else if((*this)->next != NULL)
		{
			if (strcmp(key, (*this)->next->couple.key) == 0)
				delete_LCA_solo(&((*this)->next));
			else if ((*this)->next != NULL && strcmp(key, (*this)->next->couple.key) > 0)
				delete_LCA(&((*this)->next), key);
		}
	}
}

bool has_key_LCA(LCA this, Clef key)
{
	if (this == NULL || strcmp(this->couple.key, key) > 0)
		return false;
	if (strcmp(this->couple.key, key) == 0)
		return true;
	else
		return has_key_LCA(this->next, key);
}

Donnee getValue_LCA(LCA this, Clef key)
{
	if(this != NULL && strcmp(this->couple.key, key) != 0)
		return getValue_LCA(this->next, key);
	else
		return this->couple.value;
}

void clear_LCA(LCA* this)
{
	if (*this != NULL)
	{
		clear_LCA(&((*this)->next));
		delete_LCA_solo(this);
	}
}

void destroy_LCA(LCA* this)
{
	clear_LCA(this);
	*this = NULL;
}

void print_LCA(LCA this)
{
	if (this != NULL)
	{
		printf("-->[ \"%s\"=%d ]", this->couple.key, this->couple.value);
		print_LCA(this->next);
	}
	else
		printf("--E\n");
}
