#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock iteration callbacks
static void	modify_uppercase(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

static void	modify_index_offset(unsigned int i, char *c)
{
	*c = *c + i;
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

void	test_ft_striteri(void)
{
	printf("--- Testing ft_striteri ---\n");

	// 1. Basic In-Place Modification
	{
		char str[] = "hello";
		ft_striteri(str, modify_uppercase);
		TEST_ASSERT("In-place uppercase modification", strcmp(str, "HELLO") == 0);
	}

	// 2. Index-Dependent In-Place Modification
	{
		char str[] = "00000";
		ft_striteri(str, modify_index_offset);
		TEST_ASSERT("In-place index modification ('01234')", strcmp(str, "01234") == 0);
	}

	// 3. Empty String Processing
	{
		char str[] = "";
		ft_striteri(str, modify_uppercase);
		TEST_ASSERT("Empty string remains unmodified", strcmp(str, "") == 0);
	}

	// 4. Single Character String Modification
	{
		char str[] = "a";
		ft_striteri(str, modify_uppercase);
		TEST_ASSERT("Single character modification", strcmp(str, "A") == 0);
	}

	// 5. NULL Guard Safety (if implemented in your code)
	{
		char str[] = "test";
		ft_striteri(NULL, modify_uppercase);
		TEST_ASSERT("NULL string input safety (no crash)", 1);

		ft_striteri(str, NULL);
		TEST_ASSERT("NULL function pointer safety (string unchanged)", strcmp(str, "test") == 0);
	}
}

int	main(void)
{
	test_ft_striteri();
	return (0);
}