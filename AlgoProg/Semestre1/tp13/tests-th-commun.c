#include <string.h>
#include <unistd.h>
#include "th.h"
#include "seatest.h"
#define limite 10*1000 - 1
#define logLimite 4
#define TESTS_TH

static void big_TH(TH* th)
{
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_TH(th, str, i);
	}
}

void unit_init_TH()
{
	TH th;
	INIT;
	
	assert_true(empty_TH(th));
	destroy_TH(&th);
}

void unit_empty()
{
	TH th;
	INIT;
	
	assert_true(empty_TH(th));
	add_TH(&th, "toto", 12);
	assert_false(empty_TH(th));
	
	destroy_TH(&th);
}

void unit_add()
{
	TH th;
	INIT;
	
	add_TH(&th, "toto", 12);
	assert_true(has_key_TH(th, "toto"));
	
	assert_int_equal(getValue_TH(th, "toto"), 12);
	
	add_TH(&th, "toto", 42);
	assert_int_equal(getValue_TH(th, "toto"), 42);
	
	add_TH(&th, "titi", 42);
	assert_true(has_key_TH(th, "titi"));
	
	add_TH(&th, "", 12);
	assert_true(has_key_TH(th, ""));
	
	destroy_TH(&th);
}

void unit_delete()
{
	TH th;
	INIT;
	
	add_TH(&th, "toto", 12);
	add_TH(&th, "titi", 12);
	assert_false(empty_TH(th));
	
	assert_true(has_key_TH(th, "toto"));
	delete_TH(&th, "toto");
	assert_false(has_key_TH(th, "toto"));
	
	delete_TH(&th, "toto");
	assert_false(has_key_TH(th, "toto"));
	
	big_TH(&th);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_TH(th, str));
		delete_TH(&th, str);
		assert_false(has_key_TH(th, str));
	}
	
	destroy_TH(&th);
}

void unit_has_key()
{
	TH th;
	INIT;
	
	add_TH(&th, "toto", 12);
	add_TH(&th, "titi", 12);
	
	assert_true(has_key_TH(th, "toto"));
	assert_true(has_key_TH(th, "titi"));
	
	assert_false(has_key_TH(th, "tata"));
	
	big_TH(&th);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_TH(th, str));
		delete_TH(&th, str);
		assert_false(has_key_TH(th, str));
	}
	
	destroy_TH(&th);
}

void unit_getValue()
{
	TH th;
	INIT;
	
	add_TH(&th, "toto", 12);
	add_TH(&th, "titi", 12);
	assert_false(empty_TH(th));
	
	assert_int_equal(getValue_TH(th, "toto"), 12);
	
	add_TH(&th, "toto", 42);
	assert_int_equal(getValue_TH(th, "toto"), 42);
	
	big_TH(&th);
	
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_int_equal(getValue_TH(th, str), i);
	}
	
	destroy_TH(&th);
}

void unit_clear()
{
	TH th;
	INIT;
	
	add_TH(&th, "toto", 12);
	add_TH(&th, "titi", 12);
	assert_false(empty_TH(th));
	
	clear_TH(&th);
	assert_true(empty_TH(th));
	
	big_TH(&th);
	
	assert_false(empty_TH(th));
	clear_TH(&th);
	assert_true(empty_TH(th));
	
	destroy_TH(&th);
}

void unit_destroy()
{
	TH th;
	INIT;
	
	destroy_TH(&th);
	assert_true(th == NULL);
	
	INIT;
	
	destroy_TH(&th);
	assert_true(th == NULL);
	
	INIT;
	big_TH(&th);
	
	destroy_TH(&th);
	assert_true(th == NULL);
}

void unit_print_TH()
{
	/*
	TH th;
	INIT;
	
	char buf[BUFSIZ];
    setbuf(stdout, buf);
    
    const char* filename = "unit_print_TH.txt";
    FILE* output = freopen(filename, "w", stdout);
	
	print_TH(th);
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
	
	add_TH(&th, "un", 1);
	add_TH(&th, "deux", 2);
	add_TH(&th, "trois", 3);
	add_TH(&th, "quatre", 4);
	add_TH(&th, "cinq", 5);
	add_TH(&th, "vingt-et-un", 21);
	add_TH(&th, "quatre-vingt-dix-neuf", 29);
	
	strcpy(buf, "");
	print_TH(th);
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
	
	destroy_TH(&th);
	*/
	;
}

void unit_fixture_init_TH()
{
	test_fixture_start();
	run_test(unit_init_TH);
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

void unit_fixture_print_TH()
{
	test_fixture_start();
	run_test(unit_print_TH);
	test_fixture_end();
}

void all_unit_LCA()
{
	unit_fixture_init_TH();
	unit_fixture_empty();
	unit_fixture_add();
	unit_fixture_delete();
	unit_fixture_has_key();
	unit_fixture_getValue();
	unit_fixture_clear();
	unit_fixture_destroy();
	unit_fixture_print_TH();
}
