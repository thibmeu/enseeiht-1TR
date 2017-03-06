#include <stdio.h>
#include "th.h"
#include "fonctions-hachage.h"
//-D NB_ELEMENTS 
#define logLimite 10

static void big_TH(TH* th)
{
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_TH(th, str, i);
	}
}

void perf_init_TH()
{
	TH th;
	INIT;
	
	destroy_TH(&th);
}

void perf_empty()
{
	TH th;
	INIT;
	
	empty_TH(th);
	
	big_TH(&th);
	empty_TH(th);
	
	destroy_TH(&th);
}

void perf_add()
{
	TH th;
	INIT;
	
	big_TH(&th);
	
	destroy_TH(&th);
}

void perf_delete()
{
	TH th;
	INIT;
	
	big_TH(&th);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		delete_TH(&th, str);
	}
	
	destroy_TH(&th);
}

void perf_has_key()
{
	TH th;
	INIT;
	
	big_TH(&th);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		has_key_TH(th, str);
		delete_TH(&th, str);
		has_key_TH(th, str);
	}
	
	destroy_TH(&th);
}

void perf_getValue()
{
	TH th;
	INIT;
	
	big_TH(&th);
	
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		getValue_TH(th, str);
	}
	
	destroy_TH(&th);
}

void perf_clear()
{
	TH th;
	INIT;
	
	big_TH(&th);
	
	clear_TH(&th);
	
	destroy_TH(&th);
}

void perf_destroy()
{
	TH th;
	INIT;
	big_TH(&th);
	
	destroy_TH(&th);
}

void perf_TH()
{
	perf_init_TH();
	perf_empty();
	perf_add();
	perf_delete();
	perf_has_key();
	perf_getValue();
	perf_clear();
	perf_destroy();
	//perf_print_TH();
}
