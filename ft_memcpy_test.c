
#include <assert.h>
#include <stdio.h>
#include <string.h>

void	run_test(const char *test_name, void *dest, const void *src, size_t n)
{
	char	expected[100];

	// Prepare reference result using standard memcpy
	memset(expected, 'Z', sizeof(expected));
	memset(dest, 'Z', 100);
	memcpy(expected, src, n);
	// Execute your ft_memcpy on the provided dest pointer
	ft_memcpy(dest, src, n);
	// Compare ft_memcpy output against the standard memcpy expectation
	if (memcmp(expected, dest, n) == 0)
		printf("[PASS] %s\n", test_name);
	else
	{
		printf("[FAIL] %s\n", test_name);
		printf("  Expected: \"%.*s\"\n", (int)n, expected);
		printf("  Actual:   \"%.*s\"\n", (int)n, (char *)dest);
	}
}

int	main(void)
{
	printf("=== Testing ft_memcpy ===\n\n");

	// 1. Basic String Copy
	{
		char src[] = "Hello, World!";
		char dst[20];
		run_test("Basic String Copy", dst, src, strlen(src) + 1);
	}

	// 2. Partial Copy
	{
		char src[] = "42 School";
		char dst[20];
		run_test("Partial Copy (4 bytes)", dst, src, 4);
	}

	// 3. Zero Bytes Copy
	{
		char src[] = "Do not copy";
		char dst[20] = "Original";
		run_test("Zero Bytes Copy", dst, src, 0);
	}

	// 4. Binary/Integer Array Copy
	{
		int src[] = {1, 2, 3, 4, 5};
		int dst_exp[5];
		int dst_act[5];

		memcpy(dst_exp, src, sizeof(src));
		ft_memcpy(dst_act, src, sizeof(src));

		if (memcmp(dst_exp, dst_act, sizeof(src)) == 0)
			printf("[PASS] Integer Array Copy\n");
		else
			printf("[FAIL] Integer Array Copy\n");
	}

	// 5. Return Value Check
	{
		char src[] = "Return Test";
		char dst[20];
		void *ret = ft_memcpy(dst, src, 5);

		if (ret == dst)
			printf("[PASS] Return Pointer Matches Destination\n");
		else
			printf("[FAIL] Return Pointer Mismatch\n");
	}

	// 6. Both NULL with 0 size (Libft standard edge case)
	{
		if (ft_memcpy(NULL, NULL, 0) == NULL)
			printf("[PASS] NULL, NULL with size 0 returns NULL\n");
		else
			printf("[FAIL] NULL, NULL with size 0 failed\n");
	}

	printf("\n=== Tests Completed ===\n");
	return (0);
}