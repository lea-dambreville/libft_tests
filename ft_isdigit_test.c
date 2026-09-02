#include <stdio.h>
#include <ctype.h>

// Custom assertion macro for non-terminating test output
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_isdigit(void)
{
	printf("--- Testing ft_isdigit ---\n");

	// 1. Valid Digits ('0' through '9')
	TEST_ASSERT("Digit '0'", ft_isdigit('0') != 0);
	TEST_ASSERT("Digit '5'", ft_isdigit('5') != 0);
	TEST_ASSERT("Digit '9'", ft_isdigit('9') != 0);

	// 2. Boundary Characters (ASCII 47 and ASCII 58)
	TEST_ASSERT("Character before '0' ('/')", ft_isdigit('/') == 0);
	TEST_ASSERT("Character after '9' (':')", ft_isdigit(':') == 0);

	// 3. Alphabetic & Special Characters
	TEST_ASSERT("Lowercase 'a'", ft_isdigit('a') == 0);
	TEST_ASSERT("Uppercase 'A'", ft_isdigit('A') == 0);
	TEST_ASSERT("Space ' '", ft_isdigit(' ') == 0);
	TEST_ASSERT("Punctuation '!'", ft_isdigit('!') == 0);
	TEST_ASSERT("Null byte '\\0'", ft_isdigit('\0') == 0);
	TEST_ASSERT("Newline '\\n'", ft_isdigit('\n') == 0);

	// 4. Edge Cases & Non-ASCII Integers
	TEST_ASSERT("Negative value (-1)", ft_isdigit(-1) == 0);
	TEST_ASSERT("EOF", ft_isdigit(EOF) == 0);
	TEST_ASSERT("Extended ASCII (150)", ft_isdigit(150) == 0);

	// 5. Full Parity Check with Standard ctype.h isdigit
	int match_count = 0;
	for (int i = 0; i <= 127; i++)
	{
		if ((ft_isdigit(i) != 0) == (isdigit(i) != 0))[cite: 1]
			match_count++;
	}
	TEST_ASSERT("Full 0-127 ASCII spectrum parity check", match_count == 128);
}

int	main(void)
{
	test_ft_isdigit();
	return (0);
}