#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define NCOEFF 3

/*
Cacul et affiche les racines d'un polynome de la forme
ax^2+bx+c si celle ci sont reeles
*/

int detDegre(double a, double b, double c)
// 
{
	return (a==0)?(b==0)?0:1:2;
}

double calculDiscriminant(double a, double b, double c)

{
	return b*b-4*a*c;
}

bool calculRacine(double a, double b, double c, double* racine)
// necessite
//	a != 0
{
	assert(a!=0);
	double discriminant = calculDiscriminant(a, b, c);
	if (discriminant > 0) //pour ce test, cf wikipedia 2nd degre polynome
	{
		double racineDiscri = pow(discriminant, 1/2);
		*racine = (-b-racineDiscri)/(2*a);
		*(racine+1) = (-2*c)/(b+racineDiscri);
	}
	else if (discriminant == 0) // une seule racine double
	{
		*racine = -b/(2*a);
		*(racine+1) = racine[0];
	}
	else
	{
		return false; //indique des racines non reelles
	}
	return true;
}

bool calculEnsemble(double a) //determine si c solution de a=0
{
	return a==0;
}

double calculPoint(double a, double b) //calcul x, ax+b=0
{
	return -b/a;
}

void saisiePolynome(double* coefficient)
{
	printf("Entrez les differents coefficients :");
	for (int iCoeff = 0; iCoeff < NCOEFF; iCoeff++)
		scanf("%lf", (coefficient+iCoeff));
}

int main() {
	double coefficient[NCOEFF];
	//entre le polynome
	saisiePolynome(&coefficient[0]); 	
	
	double a=coefficient[0], b=coefficient[1], c=coefficient[2];
	
	int degPoly = detDegre(a, b, c); //determine le degre du polynome
	switch (degPoly)
	{
		case 0: //c=0
		{
			if (calculEnsemble(c))
				puts("Tous les reels sont solutions\n");
			else
				puts("L'equation n'a pas de solution\n");
			break;
		}
		case 1:  //bx+c=0
		{
			double resultat = calculPoint(b, c);
			printf("x=%lf solution de l'equation\n", resultat);
			break;
		}
		case 2:  //ax^2+bx+c=0
		{
			double racine[2];
			if (calculRacine(a, b, c, &racine[0]))
			{
				if (racine[0]-racine[1]<pow(10, 8))
					printf("x=%lf est racine double du polynome\n", racine[0]);
				else
					printf("x1=%lf, x2=%lf sont racines du polynome\n", racine[0], racine[1]);
			}
			else
				printf("Le polynome n'admet pas de racine reelle\n");
			break;
		}
		default:
			printf("Cas non gere par le programme\n");
	}

	return EXIT_SUCCESS;
}
