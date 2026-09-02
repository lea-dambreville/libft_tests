#include <stdio.h>
#include <ctype.h>

// Custom macro to run and report tests safely[cite: 1]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_isalnum(void)
{
	printf("--- Testing ft_isalnum ---\n");

	// 1. Valid Alphanumeric Inputs[cite: 1]
	TEST_ASSERT("Lowercase 'a'", ft_isalnum('a') != 0);[cite: 1]
	TEST_ASSERT("Lowercase 'z'", ft_isalnum('z') != 0);[cite: 1]
	TEST_ASSERT("Uppercase 'A'", ft_isalnum('A') != 0);[cite: 1]
	TEST_ASSERT("Uppercase 'Z'", ft_isalnum('Z') != 0);[cite: 1]
	TEST_ASSERT("Digit '0'", ft_isalnum('0') != 0);[cite: 1]
	TEST_ASSERT("Digit '9'", ft_isalnum('9') != 0);[cite: 1]

	// 2. Non-Alphanumeric & ASCII Boundaries[cite: 1]
	TEST_ASSERT("Space character ' '", ft_isalnum(' ') == 0);[cite: 1]
	TEST_ASSERT("Punctuation '!'", ft_isalnum('!') == 0);[cite: 1]
	TEST_ASSERT("Punctuation '@'", ft_isalnum('@') == 0);[cite: 1]
	TEST_ASSERT("Punctuation '['", ft_isalnum('[') == 0);[cite: 1]
	TEST_ASSERT("Punctuation '`'", ft_isalnum('`') == 0);[cite: 1]
	TEST_ASSERT("Punctuation '{'", ft_isalnum('{') == 0);[cite: 1]
	TEST_ASSERT("Control character '\\n'", ft_isalnum('\n') == 0);[cite: 1]
	TEST_ASSERT("Null byte '\\0'", ft_isalnum('\0') == 0);[cite: 1]

	// 3. Out-of-bounds & Edge Values[cite: 1]
	TEST_ASSERT("Negative value (-1)", ft_isalnum(-1) == 0);[cite: 1]
	TEST_ASSERT("Extended ASCII (200)", ft_isalnum(200) == 0);[cite: 1]
	TEST_ASSERT("EOF", ft_isalnum(EOF) == 0);[cite: 1]

	// 4. Parity check with standard ctype.h isalnum[cite: 1]
	int match_count = 0;
	for (int i = 0; i <= 127; i++)
	{
		if ((ft_isalnum(i) != 0) == (isalnum(i) != 0))[cite: 1]
			match_count++;
	}
	TEST_ASSERT("Full 0-127 ASCII spectrum matching ctype.h isalnum", match_count == 128);[cite: 1]
}

int	main(void)
{
	test_ft_isalnum();
	return (0);
}