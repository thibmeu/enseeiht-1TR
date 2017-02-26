/****** C.c : Implantation du module C ******/

#include <stdio.h>
#include <stdlib.h>

#include "C.h"

static int nb_n = 0;

static void l(void)
{
    printf("---- Je suis C::l(void)\n");
}

void n(void)
{
    printf(">>>> C::n(void)\n");
    printf("Appel de C::l(void)\n");
    l();
    printf("<<<< C::m(void)\n");
    nb_n++;
}
