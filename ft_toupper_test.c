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

void	test_ft_toupper(void)
{
	printf("--- Testing ft_toupper ---\n");

	// 1. Lowercase Letters (Should convert to uppercase)
	TEST_ASSERT("Convert 'a'", ft_toupper('a') == 'A');
	TEST_ASSERT("Convert 'm'", ft_toupper('m') == 'M');
	TEST_ASSERT("Convert 'z'", ft_toupper('z') == 'Z');

	// 2. Off-By-One Range Boundaries
	TEST_ASSERT("Boundary character before 'a' ('`')", ft_toupper('`') == '`');
	TEST_ASSERT("Boundary character after 'z' ('{')", ft_toupper('{') == '{');

	// 3. Already Uppercase Letters (Should remain unchanged)
	TEST_ASSERT("Uppercase 'A'", ft_toupper('A') == 'A');
	TEST_ASSERT("Uppercase 'Z'", ft_toupper('Z') == 'Z');

	// 4. Digits, Punctuation & Control Characters (Should remain unchanged)
	TEST_ASSERT("Digit '5'", ft_toupper('5') == '5');
	TEST_ASSERT("Space ' '", ft_toupper(' ') == ' ');
	TEST_ASSERT("Punctuation '!'", ft_toupper('!') == '!');
	TEST_ASSERT("Newline '\\n'", ft_toupper('\n') == '\n');
	TEST_ASSERT("Null byte '\\0'", ft_toupper('\0') == '\0');

	// 5. Edge Cases & Non-ASCII Inputs
	TEST_ASSERT("Negative value (-1)", ft_toupper(-1) == -1);
	TEST_ASSERT("EOF", ft_toupper(EOF) == EOF);
	TEST_ASSERT("Extended ASCII (200)", ft_toupper(200) == 200);

	// 6. Full Parity Check with Standard ctype.h toupper
	int match_count = 0;
	for (int i = 0; i <= 127; i++)
	{
		if (ft_toupper(i) == toupper(i))
			match_count++;
	}
	TEST_ASSERT("Full 0-127 ASCII spectrum matching ctype.h toupper", match_count == 128);
}

int	main(void)
{
	test_ft_toupper();
	return (0);
}