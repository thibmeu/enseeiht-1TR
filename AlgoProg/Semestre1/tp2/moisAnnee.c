#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* nomMois[12] = ["Janvier", "Fevrier", "Mars", "", "", "", "", "", "", "", "", ""]; 

bool isBissextile(int annee)
{
	if (annee%4==0)
	{
		if (annee%100==0)
			return (annee%400==0);
		return true;
	}	
	return false;
}

int main()
{
	int mois, annee;
	printf("Entrez un mois et une annee : ");
	do
	{
		scanf("%d", &mois);
	} while (mois < 1 || mois > 12);
	scanf("%d", &annee);
	
	int nbJours;

	switch (mois)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		{
			nbJours = 31;
			break;
		}
		case 2:
		{
			nbJours = (isBissextile(annee))?29:28;
			break;
		}
		case 4: case 6: case 9: case 11:
		{
			nbJours = 30;
			break;
		}
		default:
			printf("Vous n'avez pas entre un mois valide\n");
	}	
	printf ("Le mois de %s %d comprend %d jours\n",nomMois[mois-1], annee, nbJours);
	
	return EXIT_SUCCESS;
}
