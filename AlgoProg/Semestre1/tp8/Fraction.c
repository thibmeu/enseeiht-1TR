#include "Fraction.h"
#include <assert.h>

static int gcd(int a, int b)
{
  int c = a % b;
  while(c != 0)
  {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}

void init_Fraction(int numerateur, int denominateur, Fraction* this)
{
	assert(denominateur != 0);
	this->numerateur = numerateur;
	this->denominateur = denominateur;
	simplifier(this);
}

void simplifier(Fraction* a)
{
	int pgcd = gcd(a->numerateur, a->denominateur);
	a->numerateur /= pgcd;
	a->denominateur /= pgcd;

	if (a->denominateur < 0)
	{
		if (a->numerateur < 0)
			a->numerateur *= -1;
		a->denominateur *= -1;
	}

	if (a->numerateur == 0)
		a->denominateur = 1;
}

void oppose(Fraction a, Fraction* resultat)
{
	resultat->numerateur = -a.numerateur;
	resultat->denominateur = a.denominateur;
}

void inverse(Fraction a, Fraction* resultat)
{
	resultat->numerateur = a.denominateur;
	resultat->denominateur = a.numerateur;
	simplifier(resultat);
}

void addition(Fraction a, Fraction b, Fraction* resultat)
{
	resultat->numerateur =  a.numerateur*b.denominateur +  b.numerateur*a.denominateur;
	resultat->denominateur = a.denominateur*b.denominateur;
	simplifier(resultat);
}

void soustraction(Fraction a, Fraction b, Fraction* resultat)
{
	b.numerateur *= -1;
	addition(a, b, resultat);
}

void multiplication(Fraction a, Fraction b, Fraction* resultat)
{
	resultat->numerateur = a.numerateur * b.numerateur;
	resultat->denominateur = a.denominateur * b.denominateur;
	simplifier(resultat);
}

void division(Fraction a, Fraction b, Fraction* resultat)
{
	inverse(b, resultat);
	multiplication(a, *resultat, resultat);
}

bool comparaison(Fraction a, Fraction b)
{
	Fraction sous;
	soustraction(a, b, &sous);
	if(sous.numerateur < 0)
		return -1;
	return sous.numerateur > 0;
}

void afficher(Fraction a)
{
	printf("%d / %d\n", a.numerateur, a.denominateur);
}
