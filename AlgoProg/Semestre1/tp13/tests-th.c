#include <stdlib.h>

size_t size;
size_t (*hash_function)(const char*);
#define INIT init_TH(&th, size, hash_function)
#include "tests-th-commun.c"
#include "fonctions-hachage.h"

void unit_TH(size_t nSize, size_t (*nHash_function)(const char*))
{
	size = nSize;
	hash_function = nHash_function;
	all_unit_LCA();
}

void all_unit_TH()
{
	size_t (*hashs[NB_HASH_FUNCTIONS])(const char*) = {taille, initiale, somme, java};
	
	for(int iSize = 1; iSize <= 1000*1000; iSize *= 10)
		for(int iHash = 0; iHash < NB_HASH_FUNCTIONS; iHash++)
			unit_TH(iSize, hashs[iHash]);
}

int main()
{
	run_tests(all_unit_TH);
	return 0;
}
