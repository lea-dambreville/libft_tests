#include <stdio.h>
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

void	test_ft_strjoin(void)
{
	printf("--- Testing ft_strjoin ---\n");

	// 1. Standard Concatenation
	{
		char *res = ft_strjoin("Hello, ", "World!");
		TEST_ASSERT("Concatenate two non-empty strings", res != NULL && strcmp(res, "Hello, World!") == 0);
		free(res);
	}

	// 2. Joining Empty Strings
	{
		char *res1 = ft_strjoin("", "World");
		TEST_ASSERT("First string empty", res1 != NULL && strcmp(res1, "World") == 0);
		free(res1);

		char *res2 = ft_strjoin("Hello", "");
		TEST_ASSERT("Second string empty", res2 != NULL && strcmp(res2, "Hello") == 0);
		free(res2);

		char *res3 = ft_strjoin("", "");
		TEST_ASSERT("Both strings empty", res3 != NULL && strcmp(res3, "") == 0);
		free(res3);
	}

	// 3. Joining Single Characters / Special Characters
	{
		char *res = ft_strjoin("A", "B");
		TEST_ASSERT("Single character concatenation", res != NULL && strcmp(res, "AB") == 0);
		free(res);

		char *res_nl = ft_strjoin("Line1\n", "Line2");
		TEST_ASSERT("Concatenation with newline", res_nl != NULL && strcmp(res_nl, "Line1\nLine2") == 0);
		free(res_nl);
	}

	// 4. Pointer Address Independence
	{
		const char *s1 = "42";
		const char *s2 = "Network";
		char *res = ft_strjoin(s1, s2);
		TEST_ASSERT("Returned string is newly allocated (different address)", res != s1 && res != s2);
		free(res);
	}

	// 5. NULL Input Guard Protection (if handled in your implementation)
	{
		char *res1 = ft_strjoin(NULL, "Test");
		TEST_ASSERT("NULL s1 input safety", res1 == NULL);

		char *res2 = ft_strjoin("Test", NULL);
		TEST_ASSERT("NULL s2 input safety", res2 == NULL);

		char *res3 = ft_strjoin(NULL, NULL);
		TEST_ASSERT("Both NULL input safety", res3 == NULL);
	}
}

int	main(void)
{
	test_ft_strjoin();
	return (0);
}