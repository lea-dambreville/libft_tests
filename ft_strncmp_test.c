#include <stdio.h>
#include <string.h>

// Custom test assertion macro[cite: 1, 3]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strncmp(void)
{
	printf("--- Testing ft_strncmp ---\n");

	// 1. Identical Strings & Basic Matches
	{
		TEST_ASSERT("Identical strings return 0", ft_strncmp("Hello", "Hello", 5) == 0);
		TEST_ASSERT("Identical strings within bound return 0", ft_strncmp("Hello World", "Hello Libft", 5) == 0);
	}

	// 2. Lexicographical Differences
	{
		TEST_ASSERT("s1 < s2 returns negative difference", ft_strncmp("abc", "abd", 3) < 0);
		TEST_ASSERT("s1 > s2 returns positive difference", ft_strncmp("abd", "abc", 3) > 0);
		TEST_ASSERT("Different lengths (s1 shorter)", ft_strncmp("abc", "abcd", 4) < 0);
		TEST_ASSERT("Different lengths (s1 longer)", ft_strncmp("abcd", "abc", 4) > 0);
	}

	// 3. Bound Limits (n Parameter) & Zero Checks
	{
		TEST_ASSERT("Difference beyond n returns 0", ft_strncmp("abc", "abd", 2) == 0);
		TEST_ASSERT("Zero length compare returns 0", ft_strncmp("abc", "xyz", 0) == 0);[cite: 2]
	}

	// 4. Unsigned Char Comparison Edge Cases
	{
		// 0x80 (128) can evaluate as negative (-128) if evaluated using signed char
		const char s1[] = "\x80";
		const char s2[] = "\x00";
		TEST_ASSERT("Unsigned byte subtraction (0x80 > 0x00)", ft_strncmp(s1, s2, 1) > 0);
	}

	// 5. Direct Parity Check with Standard libc strncmp
	{
		const char *str1 = "42Network School";
		const char *str2 = "42Network Code";
		
		TEST_ASSERT("Match libc (identical prefix)", (ft_strncmp(str1, str2, 9) == 0) == (strncmp(str1, str2, 9) == 0));
		TEST_ASSERT("Match libc (mismatch sign)", (ft_strncmp(str1, str2, 12) > 0) == (strncmp(str1, str2, 12) > 0));
		TEST_ASSERT("Match libc (n = 0)", ft_strncmp(str1, str2, 0) == strncmp(str1, str2, 0));
	}
}

int	main(void)
{
	test_ft_strncmp();
	return (0);
}