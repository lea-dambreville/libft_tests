#include <stdio.h>
#include <string.h>

// Custom non-terminating assertion macro[cite: 3, 4]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_strnstr(void)
{
	printf("--- Testing ft_strnstr ---\n");

	// 1. Basic Matching
	{
		const char *haystack = "Hello 42 Network!";
		TEST_ASSERT("Find substring '42'", ft_strnstr(haystack, "42", 17) == (haystack + 6));
		TEST_ASSERT("Find substring at start", ft_strnstr(haystack, "Hello", 17) == haystack);
		TEST_ASSERT("Find substring at end", ft_strnstr(haystack, "Network!", 17) == (haystack + 9));
		TEST_ASSERT("Missing substring returns NULL", ft_strnstr(haystack, "world", 17) == NULL);
	}

	// 2. Length (len) Bound Constraints
	{
		const char *haystack = "42 school network";
		TEST_ASSERT("Match within exact len bound", ft_strnstr(haystack, "school", 9) == (haystack + 3));
		TEST_ASSERT("Truncated len hides match", ft_strnstr(haystack, "school", 8) == NULL);[cite: 5]
		TEST_ASSERT("Zero len returns NULL for non-empty needle", ft_strnstr(haystack, "42", 0) == NULL);
	}

	// 3. Empty Needle & Special Inputs
	{
		const char *haystack = "Testing";
		TEST_ASSERT("Empty needle returns haystack pointer", ft_strnstr(haystack, "", 5) == haystack);[cite: 2, 5]
		TEST_ASSERT("Empty needle with len 0 returns haystack", ft_strnstr(haystack, "", 0) == haystack);[cite: 2, 5]
		TEST_ASSERT("Empty haystack & non-empty needle returns NULL", ft_strnstr("", "test", 5) == NULL);
		const char *haystack1 = "";
		TEST_ASSERT("Both empty returns empty haystack pointer", ft_strnstr(haystack, "", 5) == haystack1);
	}

	// 4. Overlapping Substrings & False Starts
	{
		// Checks if loop properly resets j without skipping candidate start positions
		const char *haystack = "aaabcabcd";
		TEST_ASSERT("Partial match recovery ('abc')", ft_strnstr(haystack, "abc", 9) == (haystack + 2));
		TEST_ASSERT("Repeated pattern match ('abcd')", ft_strnstr(haystack, "abcd", 9) == (haystack + 5));
	}

	// 5. Bounds Beyond Null Terminator
	{
		const char *haystack = "short\0hidden_text";
		TEST_ASSERT("Does not search beyond haystack null-terminator", ft_strnstr(haystack, "hidden", 20) == NULL);
	}
}

int	main(void)
{
	test_ft_strnstr();
	return (0);
}