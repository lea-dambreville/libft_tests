#include <stdio.h>
#include <string.h>

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strrchr(void)
{
	printf("--- Testing ft_strrchr ---\n");

	// 1. Duplicate Characters (Must return LAST occurrence)
	{
		const char *str = "banana";
		TEST_ASSERT("Last occurrence of 'a'", ft_strrchr(str, 'a') == (str + 5));
		TEST_ASSERT("Last occurrence of 'n'", ft_strrchr(str, 'n') == (str + 4));
	}

	// 2. Single Match & Edge Positions
	{
		const char *str = "42 Network";
		TEST_ASSERT("Find character at start '4'", ft_strrchr(str, '4') == str);
		TEST_ASSERT("Find character at end 'k'", ft_strrchr(str, 'k') == (str + 9));
		TEST_ASSERT("Missing character returns NULL", ft_strrchr(str, 'z') == NULL);
	}

	// 3. Searching for Null-Terminator '\0'
	{
		const char *str = "Hello World";
		TEST_ASSERT("Search for '\\0' returns pointer to terminator", ft_strrchr(str, '\0') == (str + 11));[cite: 1]
		TEST_ASSERT("Search for '\\0' in empty string", ft_strrchr("", '\0') == "");
	}

	// 4. Int Casting & Extended ASCII Values
	{
		const char *str = "abc\x80def\x80ghi";
		TEST_ASSERT("Find last occurrence with (char) int cast", ft_strrchr(str, (char)0x80) == (str + 7));[cite: 1]
		TEST_ASSERT("Character passed with int value > 255", ft_strrchr("abc", 'a' + 256) == "abc");[cite: 1]
	}

	// 5. Parity Check with Standard libc strrchr
	{
		const char *sample = "Testing Libc Parity with strrchr!";
		TEST_ASSERT("Match libc (Character present)", ft_strrchr(sample, 'r') == strrchr(sample, 'r'));
		TEST_ASSERT("Match libc (Character missing)", ft_strrchr(sample, 'z') == strrchr(sample, 'z'));
		TEST_ASSERT("Match libc (Null terminator '\\0')", ft_strrchr(sample, '\0') == strrchr(sample, '\0'));
	}
}

int	main(void)
{
	test_ft_strrchr();
	return (0);
}