/****** B.c : Implantation du module B ******/

#include <stdio.h>
#include <stdlib.h>

#include "B.h"
#include "C.h"

static void l(void)
{
    printf("---- Je suis B::l(void)\n");
}

void m(void)
{
    printf(">>>> B::m(void)\n");
    printf("Appel de C::n(void)\n");
    n();
    printf("Appel de B::l(void)\n");
    l();
    printf("<<<< B::m(void)\n");
}
