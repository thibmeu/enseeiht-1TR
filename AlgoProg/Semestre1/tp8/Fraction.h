#ifndef FRACTION_H
#define FRACTION_H

#include <stdio.h>
#include <stdbool.h>

struct Fraction
{
	int numerateur;
	int denominateur;
};
typedef struct Fraction Fraction;

void init_Fraction(int numerateur, int denominateur, Fraction* this);

void simplifier(Fraction* a);

void oppose(Fraction a, Fraction* resultat);

void inverse(Fraction a, Fraction* resultat);

void addition(Fraction a, Fraction b, Fraction* resultat);

void soustraction(Fraction a, Fraction b, Fraction* resultat);

void multiplication(Fraction a, Fraction b, Fraction* resultat);

void division(Fraction a, Fraction b, Fraction* resultat);

bool comparaison(Fraction a, Fraction b);

void afficher(Fraction a);

#endif
