#include <stdio.h>
#include "sda.h"
#include "fonctions-hachage.h"
//-D NB_ELEMENTS 
#define logLimite 10

static void big_SDA(SDA* sda)
{
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_SDA(sda, str, i);
	}
}

void perf_init_SDA()
{
	SDA sda;
	INIT;
	
	destroy_SDA(&sda);
}

void perf_empty()
{
	SDA sda;
	INIT;
	
	empty_SDA(sda);
	
	big_SDA(&sda);
	empty_SDA(sda);
	
	destroy_SDA(&sda);
}

void perf_add()
{
	SDA sda;
	INIT;
	
	big_SDA(&sda);
	
	destroy_SDA(&sda);
}

void perf_delete()
{
	SDA sda;
	INIT;
	
	big_SDA(&sda);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		delete_SDA(&sda, str);
	}
	
	destroy_SDA(&sda);
}

void perf_has_key()
{
	SDA sda;
	INIT;
	
	big_SDA(&sda);
	
	for(int i = NB_ELEMENTS-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		has_key_SDA(sda, str);
		delete_SDA(&sda, str);
		has_key_SDA(sda, str);
	}
	
	destroy_SDA(&sda);
}

void perf_getValue()
{
	SDA sda;
	INIT;
	
	big_SDA(&sda);
	
	for(int i = 0; i < NB_ELEMENTS; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		getValue_SDA(sda, str);
	}
	
	destroy_SDA(&sda);
}

void perf_clear()
{
	SDA sda;
	INIT;
	
	big_SDA(&sda);
	
	clear_SDA(&sda);
	
	destroy_SDA(&sda);
}

void perf_destroy()
{
	SDA sda;
	INIT;
	big_SDA(&sda);
	
	destroy_SDA(&sda);
}

void perf_SDA()
{
	perf_init_SDA();
	perf_empty();
	perf_add();
	perf_delete();
	perf_has_key();
	perf_getValue();
	perf_clear();
	perf_destroy();
	//perf_print_SDA();
}
