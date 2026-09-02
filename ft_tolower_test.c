#include <stdio.h>
#include <ctype.h>

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_tolower(void)
{
	printf("--- Testing ft_tolower ---\n");

	// 1. Uppercase Letters (Should convert to lowercase)
	TEST_ASSERT("Convert 'A'", ft_tolower('A') == 'a');
	TEST_ASSERT("Convert 'M'", ft_tolower('M') == 'm');
	TEST_ASSERT("Convert 'Z'", ft_tolower('Z') == 'z');

	// 2. Off-By-One Range Boundaries
	TEST_ASSERT("Boundary character before 'A' ('@')", ft_tolower('@') == '@');
	TEST_ASSERT("Boundary character after 'Z' ('[')", ft_tolower('[') == '[');

	// 3. Already Lowercase Letters (Should remain unchanged)
	TEST_ASSERT("Lowercase 'a'", ft_tolower('a') == 'a');
	TEST_ASSERT("Lowercase 'z'", ft_tolower('z') == 'z');

	// 4. Digits, Punctuation & Control Characters (Should remain unchanged)
	TEST_ASSERT("Digit '5'", ft_tolower('5') == '5');
	TEST_ASSERT("Space ' '", ft_tolower(' ') == ' ');
	TEST_ASSERT("Punctuation '!'", ft_tolower('!') == '!');
	TEST_ASSERT("Newline '\\n'", ft_tolower('\n') == '\n');
	TEST_ASSERT("Null byte '\\0'", ft_tolower('\0') == '\0');

	// 5. Edge Cases & Non-ASCII Inputs
	TEST_ASSERT("Negative value (-1)", ft_tolower(-1) == -1);
	TEST_ASSERT("EOF", ft_tolower(EOF) == EOF);
	TEST_ASSERT("Extended ASCII (200)", ft_tolower(200) == 200);

	// 6. Full Parity Check with Standard ctype.h tolower
	int match_count = 0;
	for (int i = 0; i <= 127; i++)
	{
		if (ft_tolower(i) == tolower(i))
			match_count++;
	}
	TEST_ASSERT("Full 0-127 ASCII spectrum matching ctype.h tolower", match_count == 128);
}

int	main(void)
{
	test_ft_tolower();
	return (0);
}