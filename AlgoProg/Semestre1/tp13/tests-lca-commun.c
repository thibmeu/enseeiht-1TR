#include <string.h>
#include <unistd.h>
#include "lca.h"
#include "seatest.h"
#define limite 10*1000 - 1
#define logLimite 4
#define TESTS_LCA

static void big_LCA(LCA* lca)
{
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_LCA(lca, str, i);
	}
}

void unit_init_LCA()
{
	LCA lca;
	INIT;
	
	assert_true(empty_LCA(lca));
	destroy_LCA(&lca);
}

void unit_empty()
{
	LCA lca;
	INIT;
	
	assert_true(empty_LCA(lca));
	add_LCA(&lca, "toto", 12);
	assert_false(empty_LCA(lca));
	
	destroy_LCA(&lca);
}

void unit_add()
{
	LCA lca;
	INIT;
	
	add_LCA(&lca, "toto", 12);
	assert_true(has_key_LCA(lca, "toto"));
	
	assert_int_equal(getValue_LCA(lca, "toto"), 12);
	
	add_LCA(&lca, "toto", 42);
	assert_int_equal(getValue_LCA(lca, "toto"), 42);
	
	add_LCA(&lca, "titi", 42);
	assert_true(has_key_LCA(lca, "titi"));
	
	add_LCA(&lca, "", 12);
	assert_true(has_key_LCA(lca, ""));
	
	destroy_LCA(&lca);
}

void unit_delete()
{
	LCA lca;
	INIT;
	
	add_LCA(&lca, "toto", 12);
	add_LCA(&lca, "titi", 12);
	assert_false(empty_LCA(lca));
	
	assert_true(has_key_LCA(lca, "toto"));
	delete_LCA(&lca, "toto");
	assert_false(has_key_LCA(lca, "toto"));
	
	delete_LCA(&lca, "toto");
	assert_false(has_key_LCA(lca, "toto"));
	
	big_LCA(&lca);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_LCA(lca, str));
		delete_LCA(&lca, str);
		assert_false(has_key_LCA(lca, str));
	}
	
	destroy_LCA(&lca);
}

void unit_has_key()
{
	LCA lca;
	INIT;
	
	add_LCA(&lca, "toto", 12);
	add_LCA(&lca, "titi", 12);
	
	assert_true(has_key_LCA(lca, "toto"));
	assert_true(has_key_LCA(lca, "titi"));
	
	assert_false(has_key_LCA(lca, "tata"));
	
	big_LCA(&lca);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_LCA(lca, str));
		delete_LCA(&lca, str);
		assert_false(has_key_LCA(lca, str));
	}
	
	destroy_LCA(&lca);
}

void unit_getValue()
{
	LCA lca;
	INIT;
	
	add_LCA(&lca, "toto", 12);
	add_LCA(&lca, "titi", 12);
	assert_false(empty_LCA(lca));
	
	assert_int_equal(getValue_LCA(lca, "toto"), 12);
	
	add_LCA(&lca, "toto", 42);
	assert_int_equal(getValue_LCA(lca, "toto"), 42);
	
	big_LCA(&lca);
	
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_int_equal(getValue_LCA(lca, str), i);
	}
	
	destroy_LCA(&lca);
}

void unit_clear()
{
	LCA lca;
	INIT;
	
	add_LCA(&lca, "toto", 12);
	add_LCA(&lca, "titi", 12);
	assert_false(empty_LCA(lca));
	
	clear_LCA(&lca);
	assert_true(empty_LCA(lca));
	
	big_LCA(&lca);
	
	assert_false(empty_LCA(lca));
	clear_LCA(&lca);
	assert_true(empty_LCA(lca));
	
	destroy_LCA(&lca);
}

void unit_destroy()
{
	LCA lca;
	INIT;
	
	destroy_LCA(&lca);
	assert_true(lca == NULL);
	
	INIT;
	
	destroy_LCA(&lca);
	assert_true(lca == NULL);
	
	INIT;
	big_LCA(&lca);
	
	destroy_LCA(&lca);
	assert_true(lca == NULL);
}

void unit_print_LCA()
{
	/*
	LCA lca;
	INIT;
	
	char buf[BUFSIZ];
    setbuf(stdout, buf);
    
    const char* filename = "unit_print_LCA.txt";
    FILE* output = freopen(filename, "w", stdout);
	
	print_LCA(lca);
	#ifdef TESTS_LCA
	assert_string_equal(buf, "--E\n");
	#else
	if (th->size == 10)
		assert_string_equal(buf,
	"   0[@-]--E\n\
   1[@-]--E\n\
   2[@-]--E\n\
   3[@-]--E\n\
   4[@-]--E\n\
   5[@-]--E\n\
   6[@-]--E\n\
   7[@-]--E\n\
   8[@-]--E\n\
   9[@-]--E\n\
  10[@-]--E\n");
	#endif
	
	add_LCA(&lca, "un", 1);
	add_LCA(&lca, "deux", 2);
	add_LCA(&lca, "trois", 3);
	add_LCA(&lca, "quatre", 4);
	add_LCA(&lca, "cinq", 5);
	add_LCA(&lca, "vingt-et-un", 21);
	add_LCA(&lca, "quatre-vingt-dix-neuf", 29);
	
	strcpy(buf, "");
	print_LCA(lca);
	#ifdef TESTS_LCA
	assert_string_equal(buf, "-->[ \"vingt-et-un\"=21 ]-->[ \"un\"=1 ]-->[ \"deux\"=2 ]-->[ \"trois\"=3 ]-->[ \"quatre\"=4 ]-->[ \"cinq\"=5 ]-->[ \"quatre-vingt-dix-neuf\"=29 ]--E\n");
	#else
	if (th->size == 10)
		assert_string_equal(buf, 
	"   0[@-]-->[ \"vingt-et-un\"=21 ]--E\n\
   1[@-]--E\n\
   2[@-]-->[ \"un\"=1 ]--E\n\
   3[@-]--E\n\
   4[@-]-->[ \"deux\"=2 ]-->[ \"cinq\"=5 ]--E\n\
   5[@-]-->[ \"trois\"=3 ]--E\n\
   6[@-]-->[ \"quatre\"=4 ]--E\n\
   7[@-]--E\n\
   8[@-]--E\n\
   9[@-]--E\n\
  10[@-]-->[ \"quatre-vingt-dix-neuf\"=29 ]--E\n");
	#endif
	
	fclose(output);
	freopen("/dev/null", "w", stdout);
	//freopen(stdout_back, "r", stdout);
	
	destroy_LCA(&lca);
	*/
	;
}

void unit_fixture_init_LCA()
{
	test_fixture_start();
	run_test(unit_init_LCA);
	test_fixture_end();
}

void unit_fixture_empty()
{
	test_fixture_start();
	run_test(unit_empty);
	test_fixture_end();
}

void unit_fixture_add()
{
	test_fixture_start();
	run_test(unit_add);
	test_fixture_end();
}

void unit_fixture_delete()
{
	test_fixture_start();
	run_test(unit_delete);
	test_fixture_end();
}

void unit_fixture_has_key()
{
	test_fixture_start();
	run_test(unit_has_key);
	test_fixture_end();
}

void unit_fixture_getValue()
{
	test_fixture_start();
	run_test(unit_getValue);
	test_fixture_end();
}

void unit_fixture_clear()
{
	test_fixture_start();
	run_test(unit_clear);
	test_fixture_end();
}

void unit_fixture_destroy()
{
	test_fixture_start();
	run_test(unit_destroy);
	test_fixture_end();
}

void unit_fixture_print_LCA()
{
	test_fixture_start();
	run_test(unit_print_LCA);
	test_fixture_end();
}

void all_unit_LCA()
{
	unit_fixture_init_LCA();
	unit_fixture_empty();
	unit_fixture_add();
	unit_fixture_delete();
	unit_fixture_has_key();
	unit_fixture_getValue();
	unit_fixture_clear();
	unit_fixture_destroy();
	unit_fixture_print_LCA();
}
