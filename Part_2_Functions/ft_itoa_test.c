#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_itoa(void)
{
	printf("--- Testing ft_itoa ---\n");

	// 1. Basic Positive Numbers
	{
		char *res = ft_itoa(42);
		TEST_ASSERT("Positive integer (42)", res != NULL && strcmp(res, "42") == 0);
		free(res);

		char *res_single = ft_itoa(7);
		TEST_ASSERT("Single digit (7)", res_single != NULL && strcmp(res_single, "7") == 0);
		free(res_single);
	}

	// 2. Basic Negative Numbers
	{
		char *res = ft_itoa(-42);
		TEST_ASSERT("Negative integer (-42)", res != NULL && strcmp(res, "-42") == 0);
		free(res);

		char *res_single = ft_itoa(-9);
		TEST_ASSERT("Single negative digit (-9)", res_single != NULL && strcmp(res_single, "-9") == 0);
		free(res_single);
	}

	// 3. Zero
	{
		char *res = ft_itoa(0);
		TEST_ASSERT("Zero (0)", res != NULL && strcmp(res, "0") == 0);
		free(res);
	}

	// 4. Integer Limits (INT_MAX & INT_MIN)
	{
		char *res_max = ft_itoa(INT_MAX);
		TEST_ASSERT("INT_MAX (2147483647)", res_max != NULL && strcmp(res_max, "2147483647") == 0);
		free(res_max);

		char *res_min = ft_itoa(INT_MIN);
		TEST_ASSERT("INT_MIN (-2147483648)", res_min != NULL && strcmp(res_min, "-2147483648") == 0);
		free(res_min);
	}

	// 5. Multi-digit Edge Cases
	{
		char *res_hundred = ft_itoa(100);
		TEST_ASSERT("Number with trailing zeros (100)", res_hundred != NULL && strcmp(res_hundred, "100") == 0);
		free(res_hundred);

		char *res_neg_hundred = ft_itoa(-1000);
		TEST_ASSERT("Negative with trailing zeros (-1000)", res_neg_hundred != NULL && strcmp(res_neg_hundred, "-1000") == 0);
		free(res_neg_hundred);
	}
}

int	main(void)
{
	test_ft_itoa();
	return (0);
}