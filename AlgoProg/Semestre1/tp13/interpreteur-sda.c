/*******************************************************************************
 *  Auteur   : Thibault Meunier
 *  Objectif : Interpréteur d'un fichier de commandes
 ******************************************************************************/

#define INTERPRETEUR_SDA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sda.h"
#include "fonctions-hachage.h"
#define MAX_KEYWORD 10
#define LOG_MAX_INT 5	//INT_MAX = 32767
#define MAX_SPACE 10
#define MAX_INSTRUCTION MAX_KEYWORD+MAX_KEY+LOG_MAX_INT+MAX_SPACE

const char* txtHashFunction[NB_HASH_FUNCTIONS] = {"taille", "initiale", "somme", "java"};

void instruct_size(SDA* sda, size_t size)
{
	#ifdef INTERPRETEUR_TH
	destroy_TH(th);
	init_TH(sda, size, taille);
	#endif
	;
}

void instruct_hash(SDA sda, char* txtHash)
{
	#ifdef INTERPRETEUR_TH
	size_t (*hashs[NB_HASH_FUNCTIONS])(const char*) = {taille, initiale, somme, java};
	for (int iHash = 0; iHash < NB_HASH_FUNCTIONS; iHash++)
		if(strcmp(txtHashFunction[iHash], txtHash) == 0)
			sda->hash_function = hashs[iHash];
	#endif
	;
}

void instruct_print(SDA sda)
{
	print_SDA(sda);
}

void instruct_clear(SDA* sda)
{
	clear_SDA(sda);
}

void instruct_remove(SDA* sda, Clef key)
{
	delete_SDA(sda, key);
}

void instruct_contains(SDA sda, Clef key)
{
	if (has_key_SDA(sda, key))
		printf("yes\n");
	else
		printf("no\n");
	
}

void instruct_value(SDA sda, Clef key)
{
	if (has_key_SDA(sda, key))
		printf("%d\n", getValue_SDA(sda, key));
	else
		printf("----\n");
}

void instruct_add(SDA* sda, Clef key, Donnee value)
{
	add_SDA(sda, key, value);
}

bool parser(char* instruction, SDA* sda)
{
	//Get keyword
	char* keyword = strtok(instruction, " \n");
	char* arg1 = strtok(NULL, " \n");
	char* arg2 = strtok(NULL, " \n");
	
	//Parsing
	if (strcmp(keyword, "size") == 0)
		instruct_size(sda, (size_t)(atoi(arg1)));
	if (strcmp(keyword, "hash") == 0)
		instruct_hash(*sda, arg1);
		
	if (strcmp(keyword, "print") == 0)
		instruct_print(*sda);
	if (strcmp(keyword, "clear") == 0)
		instruct_clear(sda);
	if (strcmp(keyword, "remove") == 0)
		instruct_remove(sda, arg1);
	if (strcmp(keyword, "contains") == 0)
		instruct_contains(*sda, arg1);
	if (strcmp(keyword, "value") == 0)
		instruct_value(*sda, arg1);
	if (strcmp(keyword, "add") == 0)
		instruct_add(sda, arg1, atoi(arg2));
	
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
    
    SDA sda;
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
	} while (!parser(instruction, &sda) && !feof(input));
	
	destroy_SDA(&sda);
	
	fclose(input);
	input = NULL;
	
	return 0;
}
