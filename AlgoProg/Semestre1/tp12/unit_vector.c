#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.h"

bool unit_create_expert()
{
	Vector* v = create_expert(10, 3);
	return (v != NULL) && (v->t != NULL);
}
bool unit_create()
{
	Vector* v = create();
	return (v != NULL) && (v->t != NULL);
}

bool unit_destroy()
{
	Vector* v = create();
	destroy(&v);
	return v == NULL;
}

bool unit_size()
{
	Vector* v = create();
	add(&v, 42);
	add(&v, 314);
	return (size(*v) == v->len) && (size(*v) == 2);
}

bool unit_capacity()
{
	Vector* v = create();
	add(&v, 42);
	add(&v, 314);
	return (capacity(*v) == v->trueLen) && (capacity(*v) == 10);
}

bool unit_add()
{	
	Vector* v = create();
	add(&v, 42);
	add(&v, 314);
	return ((v->t)[0] == 42) && ((v->t)[1] == 314);
}

bool unit_get();

bool unit_set();

bool unit_nRemove();

bool unit_adjust();

bool unit_insert();

bool unit_delete();

int main(int argc, char* argv[])
{
	
	printf("Test1 %d\n", unit_create_expert());
	printf("Test2 %d\n", unit_create());
	printf("Test3 %d\n", unit_destroy());
	printf("Test4 %d\n", unit_size());
	printf("Test5 %d\n", unit_capacity());

	return 0;
}
