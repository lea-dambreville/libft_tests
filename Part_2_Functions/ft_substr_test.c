
#include <stdio.h>
#include <string.h>

// Prototype for ft_substr
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Custom test assertion macro[cite: 2]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_substr(void)
{
	printf("--- Testing ft_substr ---\n");

	// 1. Standard Substring Extraction[cite: 2]
	{
		const char	*str = "Hello 42 World";
		char		*res = ft_substr(str, 6, 2);

		TEST_ASSERT("Extract middle substring ('42')", res != NULL && strcmp(res, "42") == 0);
		free(res);
	}

	// 2. Start Index Beyond String Length
	{
		const char	*str = "Hello";
		char		*res = ft_substr(str, 10, 5);

		TEST_ASSERT("Start > len returns non-NULL empty string", res != NULL && strcmp(res, "") == 0);
		free(res);
	}

	// 3. Requested Substring Length Exceeds Remaining String Length
	{
		const char	*str = "42 Network";
		char		*res = ft_substr(str, 3, 50);

		TEST_ASSERT("Truncates len to available characters ('Network')", res != NULL && strcmp(res, "Network") == 0);
		free(res);
	}

	// 4. Extracting Full String
	{
		const char	*str = "Complete";
		char		*res = ft_substr(str, 0, 8);

		TEST_ASSERT("Start at 0 with exact length copies entire string", res != NULL && strcmp(res, "Complete") == 0);
		free(res);
	}

	// 5. Zero Length Substring (len = 0)
	{
		const char	*str = "Test";
		char		*res = ft_substr(str, 2, 0);

		TEST_ASSERT("Len = 0 returns non-NULL empty string", res != NULL && strcmp(res, "") == 0);
		free(res);
	}

	// 6. Substring from Empty String
	{
		const char	*str = "";
		char		*res = ft_substr(str, 0, 5);

		TEST_ASSERT("Extraction from empty string returns empty string", res != NULL && strcmp(res, "") == 0);
		free(res);
	}

	// 7. NULL Input Safety
	{
		char *res = ft_substr(NULL, 0, 5);
		TEST_ASSERT("NULL input string safely returns NULL", res == NULL);
	}
}

int	main(void)
{
	test_ft_substr();
	return (0);
}