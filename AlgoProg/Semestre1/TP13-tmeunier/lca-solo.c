#include "lca-solo.h"
#include <stdlib.h>

void add_LCA_solo(LCA* this, Clef key, Donnee value)
{
	LCA nouv = malloc(sizeof(struct LCA));
	init_Couple(&(nouv->couple), key, value);
	nouv->next = *this;
	*this = nouv;
}

void delete_LCA_solo(LCA* this)
{
	LCA tmp = (*this)->next;
	free((*this)->couple.key);
	free(*this);
	*this = tmp;
}
