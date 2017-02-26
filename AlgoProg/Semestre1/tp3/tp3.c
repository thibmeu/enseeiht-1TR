#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define LEN_STR 100

int min(int a, int b)
{
	return (a < b)? a : b;
}


int longueur(const char* str)
/*
Prend en entree une chaine de caractere (pointeur vers le 1er element)
puis renvoie sa longueur
Assure : len >= 0
*/
{
	int len = 0;
	while (*(str+len)!='\0')
		len++;
	return len;
}

void unit_longueur()
{
	char str1[LEN_STR] = "SpicyChicken";
	char str2[LEN_STR] = "FishnChips";
	assert(longueur(str1) == 12);
	assert(longueur(str2) == 10);
	assert(longueur("") == 0);
}


void copie(const char* str1, char* str2)
/*
Initialise str2 a partir de str1
Necessite : sizeof(str1) >= sizeof(str2) 
Assure : str1 non modifiee
*/
{
	int len = longueur(str1);
	for (int i = 0; i < len; i++)
		*(str2+i) = *(str1+i);
	*(str2+len) = '\0';
}

void unit_copie()
{
	char str[LEN_STR] = "SpicyChicken";

	copie("FishnChips", str);
	assert(strcmp(str , "FishnChips"));
	
	copie("", str);
	assert(strcmp(str , ""));
}


void copieN(const char* str1, char* str2, int len)
/*
	Initialise les n = len premiers caracteres de str1 dans ceux de str2
	Necessite : len <= longueur(str1)
	Assure : str1 non modifiee
*/
{
	len = min(len, longueur(str1)); //on ne copie pas plus que la chaine
	if (longueur(str2) < len)
		*(str2+len) = '\0'; //permet de cloturer la chaine
	for (int i = 0; i < len; i++)
		*(str2+i) = *(str1+i);
	
}

void unit_copieN()
{
	char str1[STR_LEN] = "SpicyChicken";
	char str2[STR_LEN] = "FishnChips";
	char str[STR_LEN] = "";
	
	copieN(str1, str, 6);
	assert(strcmp(str, "SpicyC"));
	
	copieN(str1, str2, 5);
	assert(strcmp(str2, "SpicyChips"));
}


int compare(const char* str1, const char* str2)
/*
Donnee str1 et str2 deux chaines de caracteres, renvoie :
-1 si str1 avant str2 dans l'ordre lexicographique
0 si les chaines sont identiques
1 si str1 apres str2 dans l'ordre lexicographique
Assure : str1 et str2 non modifiees
*/
{
	int iChar = 0; //indice du caractere courant
	while (*(str1+iChar) != '\0' && *(str2+iChar) != '\0' && *(str1+iChar) == *(str2+iChar))
		iChar++;

	if (*(str1+iChar) == '\0')
	{
		if (*(str2+iChar) == '\0')
			return 0;
		return -1;
	}
	else if (*(str2+iChar) == '\0')
		return 1;
	if (*(str1+iChar) < *(str2+iChar))
		return -1;
	return 1;
}

void unit_compare()
{
	assert(strcmp("SpicyChicken", "SpicyChicken") == compare("SpicyChicken", "SpicyChicken"));
	assert(strcmp("abc", "bc") == compare("abc", "bc"));
	assert(strcmp("", "SpicyChicken") == compare("", "SpicyChicken"));
}


void concatene(const char* str1, char* str2)
/*
Ajoute str1 a la fin de str2
Necessite : sizeof(str2) >= len(str1)+len(str2)
Assure : str1 non modifiee
*/
{
	int len1 = longueur(str1);
	int len2 = longueur(str2);
	for (int iChar = 0; iChar < len2; iChar++)
		*(str2+len1+iChar) = *(str1+iChar);
	*(str2+len1+len2) = '\0';
}

void unit_concatene()
{
	;
}

int main()
{
	unit_longueur();
	unit_copie();
	unit_copieN();
	unit_compare();
	unit_concatene();
	return EXIT_SUCCESS;
}
