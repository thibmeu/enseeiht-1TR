#include "types.h"
#include <stdlib.h>
#include <string.h>

void init_Couple(Couple* this, Clef key, Donnee value)
{
	this->key = malloc((strlen(key)+1)*sizeof(char));
	strcpy(this->key, key);
	this->value = value;
}	
