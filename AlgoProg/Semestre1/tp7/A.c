/****** A.c : Implantation du module A ******/

#include <stdio.h>
#include <stdlib.h>

#include "A.h"
#include "B.h"
#include "C.h"

void f(Compteur cptr)
{
    printf(">>>> A::f(%d)\n", cptr);
    printf("Appel de B::m(void)\n");
    m();
    printf("Appel de C::n(void)\n");
    n();
    printf("<<<< A::f(void)\n");
}
