/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Interpréteur d'un fichier de commandes
 ******************************************************************************/

#define INTERPRETEUR_TH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "th.h"
#include "fonctions-hachage.h"
#define MAX_KEYWORD 10
#define LOG_MAX_INT 5	//INT_MAX = 32767
#define MAX_SPACE 10
#define MAX_INSTRUCTION MAX_KEYWORD+MAX_KEY+LOG_MAX_INT+MAX_SPACE

const char* txtHashFunction[NB_HASH_FUNCTIONS] = {"taille", "initiale", "somme", "java"};

void instruct_size(TH* th, size_t size)
{
	#ifdef INTERPRETEUR_TH
	destroy_TH(th);
	init_TH(th, size, taille);
	#endif
	;
}

void instruct_hash(TH th, char* txtHash)
{
	#ifdef INTERPRETEUR_TH
	size_t (*hashs[NB_HASH_FUNCTIONS])(const char*) = {taille, initiale, somme, java};
	for (int iHash = 0; iHash < NB_HASH_FUNCTIONS; iHash++)
		if(strcmp(txtHashFunction[iHash], txtHash) == 0)
			th->hash_function = hashs[iHash];
	#endif
	;
}

void instruct_print(TH th)
{
	print_TH(th);
}

void instruct_clear(TH* th)
{
	clear_TH(th);
}

void instruct_remove(TH* th, Clef key)
{
	delete_TH(th, key);
}

void instruct_contains(TH th, Clef key)
{
	if (has_key_TH(th, key))
		printf("yes\n");
	else
		printf("no\n");
	
}

void instruct_value(TH th, Clef key)
{
	if (has_key_TH(th, key))
		printf("%d\n", getValue_TH(th, key));
	else
		printf("----\n");
}

void instruct_add(TH* th, Clef key, Donnee value)
{
	add_TH(th, key, value);
}

bool parser(char* instruction, TH* th)
{
	//Get keyword
	char* keyword = strtok(instruction, " \n");
	char* arg1 = strtok(NULL, " \n");
	char* arg2 = strtok(NULL, " \n");
	
	//Parsing
	if (strcmp(keyword, "size") == 0)
		instruct_size(th, (size_t)(atoi(arg1)));
	if (strcmp(keyword, "hash") == 0)
		instruct_hash(*th, arg1);
		
	if (strcmp(keyword, "print") == 0)
		instruct_print(*th);
	if (strcmp(keyword, "clear") == 0)
		instruct_clear(th);
	if (strcmp(keyword, "remove") == 0)
		instruct_remove(th, arg1);
	if (strcmp(keyword, "contains") == 0)
		instruct_contains(*th, arg1);
	if (strcmp(keyword, "value") == 0)
		instruct_value(*th, arg1);
	if (strcmp(keyword, "add") == 0)
		instruct_add(th, arg1, atoi(arg2));
	
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
    
    TH th;
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
	} while (!parser(instruction, &th) && !feof(input));
	
	destroy_TH(&th);
	
	fclose(input);
	input = NULL;
	
	return 0;
}
