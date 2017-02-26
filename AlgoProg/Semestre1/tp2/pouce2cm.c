/*********************************************************************
 *  Auteur  : Thibault Meunier
 *  Version : 0.1
 *  Objectif : Conversion pouces/centimètres
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define PTOCM 2.54


void conversionPouceCentimetre()
{
	double longueur;
	char unite;

	/* Saisir la longueur */
	printf("Entrez une longueur : ");
	scanf("%lf", &longueur);
	
	do
	{
		scanf("%c", &unite);
	} while (unite == ' ');

	unite = tolower(unite);

	/* Calculer la longueur en pouces et en centimetres */
	double pouce, centimetre;
	switch (unite)
	{
		case 'p': //conversion p -> m
		{
			pouce = longueur;
			centimetre = pouce*PTOCM;
			break;
		}
		case 'm': //conversion m -> p
		{
			centimetre = longueur*100;
			pouce = centimetre/PTOCM;
			break;
		}
		case 'c': //conversion cm -> p
		{
			centimetre = longueur;
			pouce = centimetre/PTOCM;
			break;
		}
		default:
			printf("L'unite : %c n'est pas prise en charge par le programme\n", unite);
	}
	/* Afficher les resultats */
	printf("%lf p = %lf cm\n", pouce, centimetre);
}

int main()
{
	char entree;
	do
	{
		conversionPouceCentimetre();
		printf("Souhaitez vous effectuer une autre conversion ?\n");
		scanf("\n%c", &entree);
	} while (tolower(entree) != 'n');

	return EXIT_SUCCESS;
}
