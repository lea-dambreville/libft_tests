#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock mapping functions
static char	transform_uppercase(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static char	transform_index_shift(unsigned int i, char c)
{
	return (c + i);
}

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strmapi(void)
{
	printf("--- Testing ft_strmapi ---\n");

	// 1. Basic Transformation
	{
		char *res = ft_strmapi("hello", transform_uppercase);
		TEST_ASSERT("Uppercase transformation", res != NULL && strcmp(res, "HELLO") == 0);
		free(res);
	}

	// 2. Index-Dependent Transformation
	{
		char *res = ft_strmapi("00000", transform_index_shift);
		TEST_ASSERT("Index-based character offset ('01234')", res != NULL && strcmp(res, "01234") == 0);
		free(res);
	}

	// 3. Empty String Processing
	{
		char *res = ft_strmapi("", transform_uppercase);
		TEST_ASSERT("Empty string returns non-NULL empty string", res != NULL && strcmp(res, "") == 0);
		free(res);
	}

	// 4. Memory Address Independence
	{
		const char *src = "42 Network";
		char *res = ft_strmapi(src, transform_uppercase);
		TEST_ASSERT("Output is newly allocated memory address", res != NULL && res != src);
		free(res);
	}

	// 5. NULL Guard Safety (if implemented)
	{
		char *res1 = ft_strmapi(NULL, transform_uppercase);
		TEST_ASSERT("NULL string input safety", res1 == NULL);

		char *res2 = ft_strmapi("hello", NULL);
		TEST_ASSERT("NULL function pointer safety", res2 == NULL);
	}
}

int	main(void)
{
	test_ft_strmapi();
	return (0);
}