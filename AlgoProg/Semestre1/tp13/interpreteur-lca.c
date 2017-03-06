/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Interpréteur d'un fichier de commandes
 ******************************************************************************/

#define INTERPRETEUR_LCA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lca.h"
#include "fonctions-hachage.h"
#define MAX_KEYWORD 10
#define LOG_MAX_INT 5	//INT_MAX = 32767
#define MAX_SPACE 10
#define MAX_INSTRUCTION MAX_KEYWORD+MAX_KEY+LOG_MAX_INT+MAX_SPACE

const char* txtHashFunction[NB_HASH_FUNCTIONS] = {"taille", "initiale", "somme", "java"};

void instruct_size(LCA* lca, size_t size)
{
	#ifdef INTERPRETEUR_TH
	destroy_TH(th);
	init_TH(lca, size, taille);
	#endif
	;
}

void instruct_hash(LCA lca, char* txtHash)
{
	#ifdef INTERPRETEUR_TH
	size_t (*hashs[NB_HASH_FUNCTIONS])(const char*) = {taille, initiale, somme, java};
	for (int iHash = 0; iHash < NB_HASH_FUNCTIONS; iHash++)
		if(strcmp(txtHashFunction[iHash], txtHash) == 0)
			lca->hash_function = hashs[iHash];
	#endif
	;
}

void instruct_print(LCA lca)
{
	print_LCA(lca);
}

void instruct_clear(LCA* lca)
{
	clear_LCA(lca);
}

void instruct_remove(LCA* lca, Clef key)
{
	delete_LCA(lca, key);
}

void instruct_contains(LCA lca, Clef key)
{
	if (has_key_LCA(lca, key))
		printf("yes\n");
	else
		printf("no\n");
	
}

void instruct_value(LCA lca, Clef key)
{
	if (has_key_LCA(lca, key))
		printf("%d\n", getValue_LCA(lca, key));
	else
		printf("----\n");
}

void instruct_add(LCA* lca, Clef key, Donnee value)
{
	add_LCA(lca, key, value);
}

bool parser(char* instruction, LCA* lca)
{
	//Get keyword
	char* keyword = strtok(instruction, " \n");
	char* arg1 = strtok(NULL, " \n");
	char* arg2 = strtok(NULL, " \n");
	
	//Parsing
	if (strcmp(keyword, "size") == 0)
		instruct_size(lca, (size_t)(atoi(arg1)));
	if (strcmp(keyword, "hash") == 0)
		instruct_hash(*lca, arg1);
		
	if (strcmp(keyword, "print") == 0)
		instruct_print(*lca);
	if (strcmp(keyword, "clear") == 0)
		instruct_clear(lca);
	if (strcmp(keyword, "remove") == 0)
		instruct_remove(lca, arg1);
	if (strcmp(keyword, "contains") == 0)
		instruct_contains(*lca, arg1);
	if (strcmp(keyword, "value") == 0)
		instruct_value(*lca, arg1);
	if (strcmp(keyword, "add") == 0)
		instruct_add(lca, arg1, atoi(arg2));
	
	bool end = (strcmp(keyword, "end") == 0);
	
	if (!keyword)
		free(keyword);
	if (!arg1)
		free(arg1);
	if (!arg2)
		free(arg2);
	
	return end;
}

int main(int argc, char **argv)
{
    FILE* input = fopen(argv[1], "r");
    
    LCA lca;
    #ifdef INTERPRETEUR_LCA
    init_LCA(&lca);
    #else
    init_TH(&th, 10, taille);
    #endif
    
    char* instruction = malloc(MAX_INSTRUCTION+1 * sizeof(char));
    do
    {
		fgets(instruction, MAX_INSTRUCTION, input);	//on lit la ligne
		printf("> %s", instruction);
	} while (!parser(instruction, &lca) && !feof(input));
	
	destroy_LCA(&lca);
	
	fclose(input);
	input = NULL;
	
	return 0;
}
