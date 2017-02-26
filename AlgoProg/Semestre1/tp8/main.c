#include <stdio.h>
#include <stdlib.h>
#include "Fraction.h"

int main()
{
	Fraction frac1;
	init_Fraction(42, 128, &frac1);
	Fraction frac2;
	init_Fraction(12, 6, &frac2);
	
	afficher(frac1);
	afficher(frac2);
	
	inverse(frac1, &frac1);
	oppose(frac2, &frac2);
	puts("inverse oppose");
	afficher(frac1);
	afficher(frac2);

	addition(frac1, frac2, &frac1);
	soustraction(frac1, frac2, &frac1);
	puts("addition soustraction");
	afficher(frac1);

	multiplication(frac1, frac2, &frac1);
	division(frac1, frac2, &frac1);
	puts("multiplication division");
	afficher(frac1);
	
	printf("Grand : %d\n", comparaison(frac1, frac2));	
	
	return EXIT_SUCCESS;
}
