#include <stdio.h>
#include <limits.h>

// Custom test macro that reports PASS/FAIL without stopping execution
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_atoi(void)
{
	printf("--- Testing ft_atoi ---\n");

	// 1. Basic Numbers & Explicit Signs
	TEST_ASSERT("Positive number", ft_atoi("42") == 42);[cite: 1]
	TEST_ASSERT("Negative number", ft_atoi("-42") == -42);[cite: 1]
	TEST_ASSERT("Explicit positive sign", ft_atoi("+42") == 42);[cite: 1]
	TEST_ASSERT("Zero string", ft_atoi("0") == 0);[cite: 1]

	// 2. Whitespace & Control Characters
	TEST_ASSERT("Leading spaces", ft_atoi("   123") == 123);[cite: 1]
	TEST_ASSERT("Leading tabs/control chars", ft_atoi("\t\n\r\v\f123") == 123);[cite: 1]

	// 3. Early Termination & Trailing Characters
	TEST_ASSERT("Digits followed by text", ft_atoi("42abc") == 42);[cite: 1]
	TEST_ASSERT("Digits followed by spaces", ft_atoi("123   ") == 123);[cite: 1]
	TEST_ASSERT("Non-numeric start", ft_atoi("abc42") == 0);[cite: 1]
	TEST_ASSERT("Empty string", ft_atoi("") == 0);[cite: 1]

	// 4. Invalid Sign Formatting (Should terminate immediately)
	TEST_ASSERT("Multiple leading signs (--42)", ft_atoi("--42") == 0);[cite: 1]
	TEST_ASSERT("Multiple leading signs (++42)", ft_atoi("++42") == 0);[cite: 1]
	TEST_ASSERT("Space between sign and digit (- 123)", ft_atoi(" - 123") == 0);[cite: 1]

	// 5. Direct Parity Checks with Standard stdlib atoi
	TEST_ASSERT("Match stdlib (Positive)", ft_atoi("  +54321xyz") == atoi("  +54321xyz"));[cite: 1]
	TEST_ASSERT("Match stdlib (Negative)", ft_atoi(" -999") == atoi(" -999"));[cite: 1]
	TEST_ASSERT("Match stdlib (Invalid format)", ft_atoi("  - 123") == atoi("  - 123"));[cite: 1]
	TEST_ASSERT("Match stdlib (INT_MAX)", ft_atoi("2147483647") == atoi("2147483647"));
	TEST_ASSERT("Match stdlib (INT_MIN)", ft_atoi("-2147483648") == atoi("-2147483648"));
}

int	main(void)
{
	test_ft_atoi();
	return (0);
}