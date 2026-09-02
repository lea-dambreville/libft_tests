#include <stdio.h>
#include <string.h>


// Custom macro to run and report tests safely[cite: 1, 2]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strlen(void)
{
	printf("--- Testing ft_strlen ---\n");

	// 1. Basic String Testing
	TEST_ASSERT("Standard string 'Hello'", ft_strlen("Hello") == 5);
	TEST_ASSERT("Single character string", ft_strlen("a") == 1);
	TEST_ASSERT("String with spaces", ft_strlen("Hello World 42") == 14);

	// 2. Empty String Edge Case
	TEST_ASSERT("Empty string", ft_strlen("") == 0);

	// 3. Control Sequences & Special Characters
	TEST_ASSERT("String with newlines and tabs", ft_strlen("Line1\nLine2\t") == 12);
	TEST_ASSERT("String with escape characters", ft_strlen("\0hello") == 0);

	// 4. Large String
	{
		char large_str[1000];
		memset(large_str, 'A', 999);
		large_str[999] = '\0';
		TEST_ASSERT("1000-byte buffer string", ft_strlen(large_str) == 999);
	}

	// 5. Parity Check with Standard strlen
	{
		const char *sample = "Libc parity validation check!";
		TEST_ASSERT("Match standard strlen output", ft_strlen(sample) == strlen(sample));
	}
}

int	main(void)
{
	test_ft_strlen();
	return (0);
}