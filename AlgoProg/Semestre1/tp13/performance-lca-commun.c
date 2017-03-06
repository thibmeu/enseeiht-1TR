#include <stdio.h>
#include "lca.h"
#include "fonctions-hachage.h"
//-D NB_ELEMENTS 
#define logLimite 10

static void big_LCA(LCA* lca)
{
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_LCA(lca, str, i);
	}
}

void perf_init_LCA()
{
	LCA lca;
	INIT;
	
	destroy_LCA(&lca);
}

void perf_empty()
{
	LCA lca;
	INIT;
	
	empty_LCA(lca);
	
	big_LCA(&lca);
	empty_LCA(lca);
	
	destroy_LCA(&lca);
}

void perf_add()
{
	LCA lca;
	INIT;
	
	big_LCA(&lca);
	
	destroy_LCA(&lca);
}

void perf_delete()
{
	LCA lca;
	INIT;
	
	big_LCA(&lca);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		delete_LCA(&lca, str);
	}
	
	destroy_LCA(&lca);
}

void perf_has_key()
{
	LCA lca;
	INIT;
	
	big_LCA(&lca);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		has_key_LCA(lca, str);
		delete_LCA(&lca, str);
		has_key_LCA(lca, str);
	}
	
	destroy_LCA(&lca);
}

void perf_getValue()
{
	LCA lca;
	INIT;
	
	big_LCA(&lca);
	
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		getValue_LCA(lca, str);
	}
	
	destroy_LCA(&lca);
}

void perf_clear()
{
	LCA lca;
	INIT;
	
	big_LCA(&lca);
	
	clear_LCA(&lca);
	
	destroy_LCA(&lca);
}

void perf_destroy()
{
	LCA lca;
	INIT;
	big_LCA(&lca);
	
	destroy_LCA(&lca);
}

void perf_LCA()
{
	perf_init_LCA();
	perf_empty();
	perf_add();
	perf_delete();
	perf_has_key();
	perf_getValue();
	perf_clear();
	perf_destroy();
	//perf_print_LCA();
}
