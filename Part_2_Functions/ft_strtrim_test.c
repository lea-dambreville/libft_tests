#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Non-terminating test assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strtrim(void)
{
	printf("--- Testing ft_strtrim ---\n");

	// 1. Basic Trimming (Both Sides)
	{
		char *res = ft_strtrim("   Hello World!   ", " ");
		TEST_ASSERT("Trim leading and trailing spaces", res != NULL && strcmp(res, "Hello World!") == 0);
		free(res);

		char *res_multi = ft_strtrim("...---Hello World!---...", ".-");
		TEST_ASSERT("Trim set with multiple characters", res_multi != NULL && strcmp(res_multi, "Hello World!") == 0);
		free(res_multi);
	}

	// 2. Trimming Only One Side
	{
		char *res_start = ft_strtrim("xxxHello World!", "x");
		TEST_ASSERT("Trim leading characters only", res_start != NULL && strcmp(res_start, "Hello World!") == 0);
		free(res_start);

		char *res_end = ft_strtrim("Hello World!zzz", "z");
		TEST_ASSERT("Trim trailing characters only", res_end != NULL && strcmp(res_end, "Hello World!") == 0);
		free(res_end);
	}

	// 3. String Trims Completely (All characters match set)
	{
		char *res = ft_strtrim("aaaaa", "a");
		TEST_ASSERT("Trimming all matching characters returns empty string", res != NULL && strcmp(res, "") == 0);
		free(res);

		char *res_mix = ft_strtrim("abcba", "abc");
		TEST_ASSERT("Trimming full string with mixed set returns empty string", res_mix != NULL && strcmp(res_mix, "") == 0);
		free(res_mix);
	}

	// 4. No Characters Trimmed
	{
		char *res = ft_strtrim("42 Network", "xyz");
		TEST_ASSERT("No matching characters returns duplicate string", res != NULL && strcmp(res, "42 Network") == 0);
		free(res);
	}

	// 5. Empty Input or Set
	{
		char *res1 = ft_strtrim("", "abc");
		TEST_ASSERT("Empty string input returns non-NULL empty string", res1 != NULL && strcmp(res1, "") == 0);
		free(res1);

		char *res2 = ft_strtrim("Hello World", "");
		TEST_ASSERT("Empty trim set returns exact duplicate", res2 != NULL && strcmp(res2, "Hello World") == 0);
		free(res2);

		char *res3 = ft_strtrim("", "");
		TEST_ASSERT("Empty string and set returns empty string", res3 != NULL && strcmp(res3, "") == 0);
		free(res3);
	}

	// 6. Memory Allocation Independence
	{
		const char *s1 = "Test";
		char *res = ft_strtrim(s1, "x");
		TEST_ASSERT("Output is newly allocated memory address", res != NULL && res != s1);
		free(res);
	}

	// 7. NULL Input Safety (If handled in your implementation)
	{
		char *res1 = ft_strtrim(NULL, "abc");
		TEST_ASSERT("NULL s1 parameter safety", res1 == NULL);

		char *res2 = ft_strtrim("Test", NULL);
		TEST_ASSERT("NULL set parameter safety", res2 == NULL);

		char *res3 = ft_strtrim(NULL, NULL);
		TEST_ASSERT("Both parameters NULL safety", res3 == NULL);
	}
}

int	main(void)
{
	test_ft_strtrim();
	return (0);
}