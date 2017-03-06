#include <string.h>
#include <unistd.h>
#include "sda.h"
#include "seatest.h"
#define limite 10*1000 - 1
#define logLimite 4
#define TESTS_SDA

static void big_SDA(SDA* sda)
{
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];	//+1 for end of string '\0'
		sprintf(str, "%d", i);
		add_SDA(sda, str, i);
	}
}

void unit_init_SDA()
{
	SDA sda;
	INIT;
	
	assert_true(empty_SDA(sda));
	destroy_SDA(&sda);
}

void unit_empty()
{
	SDA sda;
	INIT;
	
	assert_true(empty_SDA(sda));
	add_SDA(&sda, "toto", 12);
	assert_false(empty_SDA(sda));
	
	destroy_SDA(&sda);
}

void unit_add()
{
	SDA sda;
	INIT;
	
	add_SDA(&sda, "toto", 12);
	assert_true(has_key_SDA(sda, "toto"));
	
	assert_int_equal(getValue_SDA(sda, "toto"), 12);
	
	add_SDA(&sda, "toto", 42);
	assert_int_equal(getValue_SDA(sda, "toto"), 42);
	
	add_SDA(&sda, "titi", 42);
	assert_true(has_key_SDA(sda, "titi"));
	
	add_SDA(&sda, "", 12);
	assert_true(has_key_SDA(sda, ""));
	
	destroy_SDA(&sda);
}

void unit_delete()
{
	SDA sda;
	INIT;
	
	add_SDA(&sda, "toto", 12);
	add_SDA(&sda, "titi", 12);
	assert_false(empty_SDA(sda));
	
	assert_true(has_key_SDA(sda, "toto"));
	delete_SDA(&sda, "toto");
	assert_false(has_key_SDA(sda, "toto"));
	
	delete_SDA(&sda, "toto");
	assert_false(has_key_SDA(sda, "toto"));
	
	big_SDA(&sda);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_SDA(sda, str));
		delete_SDA(&sda, str);
		assert_false(has_key_SDA(sda, str));
	}
	
	destroy_SDA(&sda);
}

void unit_has_key()
{
	SDA sda;
	INIT;
	
	add_SDA(&sda, "toto", 12);
	add_SDA(&sda, "titi", 12);
	
	assert_true(has_key_SDA(sda, "toto"));
	assert_true(has_key_SDA(sda, "titi"));
	
	assert_false(has_key_SDA(sda, "tata"));
	
	big_SDA(&sda);
	
	for(int i = limite-1; i >= 0; i--)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_true(has_key_SDA(sda, str));
		delete_SDA(&sda, str);
		assert_false(has_key_SDA(sda, str));
	}
	
	destroy_SDA(&sda);
}

void unit_getValue()
{
	SDA sda;
	INIT;
	
	add_SDA(&sda, "toto", 12);
	add_SDA(&sda, "titi", 12);
	assert_false(empty_SDA(sda));
	
	assert_int_equal(getValue_SDA(sda, "toto"), 12);
	
	add_SDA(&sda, "toto", 42);
	assert_int_equal(getValue_SDA(sda, "toto"), 42);
	
	big_SDA(&sda);
	
	for(int i = 0; i < limite; i++)
	{
		char str[logLimite+1];
		sprintf(str, "%d", i);
		assert_int_equal(getValue_SDA(sda, str), i);
	}
	
	destroy_SDA(&sda);
}

void unit_clear()
{
	SDA sda;
	INIT;
	
	add_SDA(&sda, "toto", 12);
	add_SDA(&sda, "titi", 12);
	assert_false(empty_SDA(sda));
	
	clear_SDA(&sda);
	assert_true(empty_SDA(sda));
	
	big_SDA(&sda);
	
	assert_false(empty_SDA(sda));
	clear_SDA(&sda);
	assert_true(empty_SDA(sda));
	
	destroy_SDA(&sda);
}

void unit_destroy()
{
	SDA sda;
	INIT;
	
	destroy_SDA(&sda);
	assert_true(sda == NULL);
	
	INIT;
	
	destroy_SDA(&sda);
	assert_true(sda == NULL);
	
	INIT;
	big_SDA(&sda);
	
	destroy_SDA(&sda);
	assert_true(sda == NULL);
}

void unit_print_SDA()
{
	/*
	SDA sda;
	INIT;
	
	char buf[BUFSIZ];
    setbuf(stdout, buf);
    
    const char* filename = "unit_print_SDA.txt";
    FILE* output = freopen(filename, "w", stdout);
	
	print_SDA(sda);
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
	
	add_SDA(&sda, "un", 1);
	add_SDA(&sda, "deux", 2);
	add_SDA(&sda, "trois", 3);
	add_SDA(&sda, "quatre", 4);
	add_SDA(&sda, "cinq", 5);
	add_SDA(&sda, "vingt-et-un", 21);
	add_SDA(&sda, "quatre-vingt-dix-neuf", 29);
	
	strcpy(buf, "");
	print_SDA(sda);
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
	
	destroy_SDA(&sda);
	*/
	;
}

void unit_fixture_init_SDA()
{
	test_fixture_start();
	run_test(unit_init_SDA);
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

void unit_fixture_print_SDA()
{
	test_fixture_start();
	run_test(unit_print_SDA);
	test_fixture_end();
}

void all_unit_LCA()
{
	unit_fixture_init_SDA();
	unit_fixture_empty();
	unit_fixture_add();
	unit_fixture_delete();
	unit_fixture_has_key();
	unit_fixture_getValue();
	unit_fixture_clear();
	unit_fixture_destroy();
	unit_fixture_print_SDA();
}
