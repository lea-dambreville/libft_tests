#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper to free allocated array of strings
static void	free_split(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Custom assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_split(void)
{
	printf("--- Testing ft_split ---\n");

	// 1. Standard Splitting
	{
		char	**res = ft_split("hello world 42", ' ');
		int		ok = (res && res[0] && strcmp(res[0], "hello") == 0 &&
		               res[1] && strcmp(res[1], "world") == 0 &&
		               res[2] && strcmp(res[2], "42") == 0 &&
		               res[3] == NULL);
		TEST_ASSERT("Standard multi-word split", ok);
		free_split(res);
	}

	// 2. Consecutive Delimiters
	{
		char	**res = ft_split("   hello   world   ", ' ');
		int		ok = (res && res[0] && strcmp(res[0], "hello") == 0 &&
		               res[1] && strcmp(res[1], "world") == 0 &&
		               res[2] == NULL);
		TEST_ASSERT("Handles consecutive delimiters correctly", ok);
		free_split(res);
	}

	// 3. No Delimiters Present
	{
		char	**res = ft_split("helloworld", ' ');
		int		ok = (res && res[0] && strcmp(res[0], "helloworld") == 0 &&
		               res[1] == NULL);
		TEST_ASSERT("String without delimiters returns single element array", ok);
		free_split(res);
	}

	// 4. Delimiter Not Found In Set
	{
		char	**res = ft_split("a,b,c", ' ');
		int		ok = (res && res[0] && strcmp(res[0], "a,b,c") == 0 &&
		               res[1] == NULL);
		TEST_ASSERT("Unmatched delimiter treats string as single word", ok);
		free_split(res);
	}

	// 5. String Consists Only of Delimiters
	{
		char	**res = ft_split("*****", '*');
		int		ok = (res && res[0] == NULL);
		TEST_ASSERT("All-delimiter string returns array with NULL at index 0", ok);
		free_split(res);
	}

	// 6. Empty String Input
	{
		char	**res = ft_split("", 'z');
		int		ok = (res && res[0] == NULL);
		TEST_ASSERT("Empty string returns array with NULL at index 0", ok);
		free_split(res);
	}

	// 7. NULL String Guard (if implemented)
	{
		char	**res = ft_split(NULL, ' ');
		TEST_ASSERT("NULL input safety returns NULL pointer", res == NULL);
	}
}

int	main(void)
{
	test_ft_split();
	return (0);
}