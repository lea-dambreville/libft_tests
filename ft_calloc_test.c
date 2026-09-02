#include <stdio.h>
#include <string.h>
#include <stdint.h>


// Custom test assertion macro[cite: 2]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_calloc(void)
{
	printf("--- Testing ft_calloc ---\n");

	// 1. Basic Allocation & Zero-Initialization
	{
		size_t	count = 10;
		int		*arr = (int *)ft_calloc(count, sizeof(int));
		int		all_zeros = 1;

		if (arr != NULL)
		{
			for (size_t i = 0; i < count; i++)
			{
				if (arr[i] != 0)
					all_zeros = 0;
			}
			TEST_ASSERT("Allocates and zero-initializes int array", all_zeros == 1);
			free(arr);
		}
		else
		{
			TEST_ASSERT("Allocates and zero-initializes int array", 0);
		}
	}

	// 2. Allocation with 0 Count or 0 Size
	{
		void *ptr1 = ft_calloc(0, sizeof(int));
		TEST_ASSERT("Calloc with count=0 returns non-NULL (or valid freeable pointer)", ptr1 != NULL);
		free(ptr1);

		void *ptr2 = ft_calloc(10, 0);
		TEST_ASSERT("Calloc with size=0 returns non-NULL (or valid freeable pointer)", ptr2 != NULL);
		free(ptr2);
	}

	// 3. Overflow Protection (SIZE_MAX)
	{
		void *overflow_ptr = ft_calloc(SIZE_MAX, SIZE_MAX);
		TEST_ASSERT("Overflow request returns NULL", overflow_ptr == NULL);
	}
}

int	main(void)
{
	test_ft_calloc();
	return (0);
}