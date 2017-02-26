/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Implantation de la LCA
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lca.h"

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
	LCA cur = *this;
	
	if(*this == NULL || strcmp((*this)->couple.key, key) == -1)
		add_LCA_solo(this, key, value);
	else if (strcmp((*this)->couple.key, key) == 0)
		(*this)->couple.value = value;
	else
	{
		LCA next = cur->next;
		bool noTouch = true;
		
		while (noTouch)
		{
			if(next == NULL || strcmp(next->couple.key, key) == -1)
			{
				add_LCA_solo(&(cur->next), key, value);
				noTouch = false;
			}
			else if(strcmp(next->couple.key, key) == 0)
			{
				next->couple.value = value;
				noTouch = false;
			}
			else
			{
				cur = next;
				next = next->next;
			}
		}
	}
}

void delete_LCA(LCA* this, Clef key)
{
	LCA cur = *this;
	
	if(cur != NULL)
	{
		LCA next = cur->next;
		bool noTouch = true;
		
		if (strcmp(cur->couple.key, key) == 0)
		{
			delete_LCA_solo(this);
			noTouch = false;
		}

		while (next != NULL && noTouch)
		{
			if (strcmp(next->couple.key, key) == 0)
			{
				delete_LCA_solo(&(cur->next));
				noTouch = false;
			}
			else
			{
				cur = next;
				next = next->next;
			}
		}
	}
}

bool has_key_LCA(LCA this, Clef key)
{
	while (this != NULL && strcmp(this->couple.key, key) != 0)
		this = this->next;
	return this != NULL && strcmp(this->couple.key, key) == 0;
}

Donnee getValue_LCA(LCA this, Clef key)
{
	while (this != NULL && strcmp(this->couple.key, key) != 0)
		this = this->next;
	return this->couple.value;
}

void clear_LCA(LCA* this)
{
	while(*this != NULL)
		delete_LCA_solo(this);
}

void destroy_LCA(LCA* this)
{
	clear_LCA(this);
}

void print_LCA(LCA this)
{
	while(this != NULL)
	{
		printf("-->[ \"%s\"=%d ]", this->couple.key, this->couple.value);
		this = this->next;
	}
	printf("--E\n");
}
