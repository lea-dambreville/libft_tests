#include <stdio.h>
#include <ctype.h>

// Custom macro to run and report tests safely
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_isprint(void)
{
	printf("--- Testing ft_isprint ---\n");

	// 1. Valid Printable Characters (ASCII 32 to 126)
	TEST_ASSERT("Space ' ' (ASCII 32)", ft_isprint(' ') != 0);
	TEST_ASSERT("Lowercase 'a'", ft_isprint('a') != 0);
	TEST_ASSERT("Uppercase 'Z'", ft_isprint('Z') != 0);
	TEST_ASSERT("Digit '5'", ft_isprint('5') != 0);
	TEST_ASSERT("Punctuation '!'", ft_isprint('!') != 0);
	TEST_ASSERT("Tilde '~' (ASCII 126)", ft_isprint('~') != 0);

	// 2. Off-By-One Range Boundaries
	TEST_ASSERT("ASCII 31 (Unit Separator - non-printable)", ft_isprint(31) == 0);
	TEST_ASSERT("ASCII 127 (DEL - non-printable)", ft_isprint(127) == 0);

	// 3. Control Characters & Special Bytes
	TEST_ASSERT("Null byte '\\0' (ASCII 0)", ft_isprint('\0') == 0);
	TEST_ASSERT("Tab '\\t' (ASCII 9)", ft_isprint('\t') == 0);
	TEST_ASSERT("Newline '\\n' (ASCII 10)", ft_isprint('\n') == 0);
	TEST_ASSERT("Carriage return '\\r' (ASCII 13)", ft_isprint('\r') == 0);

	// 4. Out-of-bounds & Negative Values
	TEST_ASSERT("Negative value (-1)", ft_isprint(-1) == 0);
	TEST_ASSERT("EOF", ft_isprint(EOF) == 0);
	TEST_ASSERT("Extended ASCII (128)", ft_isprint(128) == 0);
	TEST_ASSERT("Extended ASCII (200)", ft_isprint(200) == 0);

	// 5. Full Parity Check with Standard ctype.h isprint
	int match_count = 0;
	for (int i = 0; i <= 127; i++)
	{
		if ((ft_isprint(i) != 0) == (isprint(i) != 0))
			match_count++;
	}
	TEST_ASSERT("Full 0-127 ASCII spectrum matching ctype.h isprint", match_count == 128);
}

int	main(void)
{
	test_ft_isprint();
	return (0);
}