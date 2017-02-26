// Comprendre la portée des variables,
// et le masquage.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 10;
    int *p = NULL;
    printf("&n = %p\n", &n);
    printf("p = %p\n", p);
    {
	int a = 5;
	p = &a;
	printf("&a = %p\n", &a);
	printf("p = %p\n", p);
	printf("*p = %d\n", *p);
    }
    printf("p = %p\n", p);
    printf("*p = %d\n", *p);
    {
	int n = 7;
	printf("n = %d\n", n);
	printf("&n = %p\n", &n);
    }
    printf("p = %p\n", p);
    printf("*p = %d\n", *p);
    printf("n = %d\n", n);
    {
	double r = 11e102;
	printf("r = %f\n", r);
	printf("&r = %p\n", &r);
    }
    printf("*p = %d\n", *p);

    return EXIT_SUCCESS;
}
