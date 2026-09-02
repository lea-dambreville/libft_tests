// TEST
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strdup(void)
{
	printf("\n--- Testing ft_strdup ---\n");

	// 1. Basic String Duplication
	{
		const char	*original = "Hello, Libft!";
		char		*dup = ft_strdup(original);

		TEST_ASSERT("Pointer is non-NULL", dup != NULL);
		TEST_ASSERT("Contents match original string", strcmp(dup, original) == 0);
		TEST_ASSERT("Pointer address is different from original", dup != original);
		
		if (dup != NULL)
		{
			dup[0] = 'h'; // Ensure returned memory is writable heap memory
			TEST_ASSERT("Duplicate memory is writable", dup[0] == 'h' && original[0] == 'H');
			free(dup);
		}
	}

	// 2. Empty String Duplication
	{
		const char	*empty = "";
		char		*dup = ft_strdup(empty);

		TEST_ASSERT("Empty string returns non-NULL", dup != NULL);
		TEST_ASSERT("Empty string duplicate has length 0", strlen(dup) == 0);
		TEST_ASSERT("Empty string copy matches null byte", dup[0] == '\0');
		free(dup);
	}

	// 3. Large String Duplication
	{
		char large_str[1000];
		memset(large_str, 'A', 999);
		large_str[999] = '\0';

		char *dup = ft_strdup(large_str);
		TEST_ASSERT("Large string duplicated correctly", dup && strcmp(dup, large_str) == 0);
		free(dup);
	}
}

int	main(void)
{
	test_ft_strdup();
	return (0);
}