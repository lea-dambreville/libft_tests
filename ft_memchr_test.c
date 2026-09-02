#include <stdio.h>
#include <string.h>

// Custom test assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_memchr(void)
{
	printf("--- Testing ft_memchr ---\n");

	// 1. Basic Character Search in Strings
	{
		const char *str = "Hello, 42 Network!";
		TEST_ASSERT("Find character '4'", ft_memchr(str, '4', 18) == (str + 7));
		TEST_ASSERT("Find character at start 'H'", ft_memchr(str, 'H', 18) == str);
		TEST_ASSERT("Find character at end '!'", ft_memchr(str, '!', 18) == (str + 17));
		TEST_ASSERT("Character not present returns NULL", ft_memchr(str, 'z', 18) == NULL);
	}

	// 2. Search Bound Limits (n Parameter)
	{
		const char *str = "42 school";
		TEST_ASSERT("Find character within n bounds", ft_memchr(str, 'c', 6) == (str + 4));
		TEST_ASSERT("Character beyond n bounds returns NULL", ft_memchr(str, 'c', 4) == NULL);
		TEST_ASSERT("Zero n length returns NULL", ft_memchr(str, '4', 0) == NULL);
	}

	// 3. Binary Data & Embedded Null Bytes
	{
		const char data[] = {'a', 'b', '\0', 'c', 'd', '\0', 'e'};
		TEST_ASSERT("Find embedded null byte", ft_memchr(data, '\0', 7) == (data + 2));
		TEST_ASSERT("Find character after null byte", ft_memchr(data, 'd', 7) == (data + 4));
	}

	// 4. Extended ASCII & Unsigned Char Casting
	{
		// 0x80 (128) passed as int -128 or 128 depending on char signedness
		const unsigned char bytes[] = {0x10, 0x20, 0x80, 0xFF, 0x40};
		TEST_ASSERT("Find extended ASCII byte (0x80)", ft_memchr(bytes, 0x80, 5) == (bytes + 2));
		TEST_ASSERT("Find byte passed as negative int", ft_memchr(bytes, (char)0x80, 5) == (bytes + 2));
	}

	// 5. Parity Check with Standard stdlib memchr
	{
		const char *sample = "Testing string comparison with libc!";
		TEST_ASSERT("Match libc (Character present)", ft_memchr(sample, 'c', 36) == memchr(sample, 'c', 36));
		TEST_ASSERT("Match libc (Character missing)", ft_memchr(sample, 'z', 36) == memchr(sample, 'z', 36));
		TEST_ASSERT("Match libc (Search byte 0)", ft_memchr(sample, 0, 36) == memchr(sample, 0, 36));
	}
}

int	main(void)
{
	test_ft_memchr();
	return (0);
}