#include <stdio.h>
#include <string.h>

// Custom test assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \git
	} while (0)

void	test_ft_strchr(void)
{
	printf("--- Testing ft_strchr ---\n");

	// 1. Basic Character Matching & Offsets
	{
		const char *str = "42 Network School";
		TEST_ASSERT("Find character '4'", ft_strchr(str, '4') == str);
		TEST_ASSERT("Find character 'N'", ft_strchr(str, 'N') == (str + 3));
		TEST_ASSERT("Find character at end 'l'", ft_strchr(str, 'l') == (str + 16));
		TEST_ASSERT("Character missing returns NULL", ft_strchr(str, 'z') == NULL);
	}

	// 2. Duplicate Characters (Must return FIRST occurrence)
	{
		const char *str = "banana";
		TEST_ASSERT("First occurrence of 'a'", ft_strchr(str, 'a') == (str + 1));
		TEST_ASSERT("First occurrence of 'n'", ft_strchr(str, 'n') == (str + 2));
	}

	// 3. Null-Terminator Search Edge Case
	{
		const char *str = "Hello";
		TEST_ASSERT("Search for '\\0' returns pointer to null terminator", ft_strchr(str, '\0') == (str + 5));
		TEST_ASSERT("Search for empty string '\\0'", ft_strchr("", '\0') == "");
	}

	// 4. Int to Char Conversion & Negative ASCII Values
	{
		const char *str = "abc\x80def";
		TEST_ASSERT("Find character passed as (char) int cast", ft_strchr(str, (char)0x80) == (str + 3));
		TEST_ASSERT("Find int larger than 255 (int overflow bit shift)", ft_strchr("abc", 'a' + 256) == "abc");
	}

	// 5. Direct Parity Check with Standard libc strchr
	{
		const char *sample = "Testing Libc Parity!";
		TEST_ASSERT("Match libc (Character present)", ft_strchr(sample, 'P') == strchr(sample, 'P'));
		TEST_ASSERT("Match libc (Character missing)", ft_strchr(sample, 'x') == strchr(sample, 'x'));
		TEST_ASSERT("Match libc (Null terminator '\\0')", ft_strchr(sample, '\0') == strchr(sample, '\0'));
	}
}

int	main(void)
{
	test_ft_strchr();
	return (0);
}