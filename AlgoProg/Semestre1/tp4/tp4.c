#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#define NB_CARTES 52
#define NB_COULEURS 4
#define NB_VALEURS 13


enum Couleur {Pique, Coeur, Carreau, Trefle};
typedef enum Couleur Couleur;
enum Valeur {As, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi};
typedef enum Valeur Valeur;

struct Carte
{
	Couleur couleur;
	Valeur valeur;
};
typedef struct Carte Carte;

void init_Carte(Carte* carte, Couleur couleur, Valeur valeur)
{
	(*carte).couleur = couleur;
	(*carte).valeur = valeur;
};

typedef Carte Jeu52 [NB_CARTES];

void init_Jeu52(Jeu52 jeu)
{
	for(int iCouleur = 0; iCouleur < NB_COULEURS; iCouleur++)
		for(int iValeur = 0; iValeur < NB_VALEURS; iValeur++)
		{
			Carte iCarte = {iCouleur, iValeur};
			*(jeu+iCouleur*NB_VALEURS+iValeur) = iCarte;
		}
}

void permuter(Jeu52 jeu)
{
	int iCarte1 = rand()%NB_CARTES;
	int iCarte2 = rand()%NB_CARTES;
	Carte temp = *(jeu+iCarte1);
	*(jeu+iCarte1) = *(jeu+iCarte2);
	*(jeu+iCarte2) = temp;
}

void battre(Jeu52 jeu)
{
	const int NB_BATTUES = 10*1000;
	for(int iBattue = 0; iBattue < NB_BATTUES; iBattue++)
		permuter(jeu);
}

void calculPosCartes(Jeu52 jeu, int posCarte[NB_CARTES])
{
	for(int iCarte = 0; iCarte < NB_CARTES; iCarte++)
	{
		int iCouleur = (*(jeu+iCarte)).couleur;
		int iValeur = (*(jeu+iCarte)).valeur;
		posCarte[iCouleur*NB_VALEURS+iValeur] = iCarte;
	}
	
}

void affichage(Jeu52 jeu)
{
	int posCarte[NB_CARTES];
	calculPosCartes(jeu, posCarte);
	for(int iCarte = 0; iCarte < NB_CARTES; iCarte++)
		printf("%d ", posCarte[iCarte]);
	puts("");
}

bool bienBattu(Jeu52 jeu)
{
	int posCarte[NB_CARTES];
	calculPosCartes(jeu, posCarte);
	for(int iCarte = 0; iCarte < NB_CARTES-1; iCarte++)
		if ((posCarte[iCarte]+1 == posCarte[iCarte+1]) || posCarte[iCarte] < 0 || posCarte[iCarte] >= NB_CARTES)
			return false;
	return (posCarte[NB_CARTES-1] < NB_CARTES && posCarte[NB_CARTES-1] >= 0);
}

int main()
{
	srand(time(NULL));
	
	Jeu52 jeu;
	init_Jeu52(jeu);
	affichage(jeu);
	
	battre(jeu);
	affichage(jeu);
	printf("%d\n", bienBattu(jeu));
	
	return EXIT_SUCCESS;
}
