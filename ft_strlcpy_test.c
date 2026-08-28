
#include <stdio.h>
#include <string.h>
#include <assert.h>

static void	test_normal_copy(void)
{
	char		dst[20];
	const char	*src = "Hello World";
	size_t		ret;

	memset(dst, 'A', sizeof(dst));
	ret = ft_strlcpy(dst, src, sizeof(dst));

	// 1. Check return value (must equal src length)
	assert(ret == strlen(src));
	// 2. Check destination contents
	assert(strcmp(dst, "Hello World") == 0);

	printf("[PASS] Normal Copy\n");
}

static void	test_truncation(void)
{
	char		dst[6]; // Space for 5 chars + '\0'
	const char	*src = "Hello World"; // 11 chars
	size_t		ret;

	memset(dst, 'A', sizeof(dst));
	ret = ft_strlcpy(dst, src, sizeof(dst));

	// 1. Return value MUST still be full src length (11)
	assert(ret == strlen(src));
	// 2. Output must be safely truncated to fit dst size - 1 ("Hello")
	assert(strcmp(dst, "Hello") == 0);
	// 3. Must be properly null-terminated at index size - 1
	assert(dst[5] == '\0');

	printf("[PASS] Truncated Buffer\n");
}

static void	test_zero_size(void)
{
	char		dst[10] = "Original";
	const char	*src = "New String";
	size_t		ret;

	ret = ft_strlcpy(dst, src, 0);

	// 1. Return value must still be full src length
	assert(ret == strlen(src));
	// 2. Destination buffer must remain COMPLETELY untouched
	assert(strcmp(dst, "Original") == 0);

	printf("[PASS] Zero Size Buffer\n");
}

static void	test_exact_fit(void)
{
	char		dst[6]; // Exactly fits "Hello" + '\0'
	const char	*src = "Hello";
	size_t		ret;

	ret = ft_strlcpy(dst, src, sizeof(dst));

	assert(ret == strlen(src));
	assert(strcmp(dst, "Hello") == 0);

	printf("[PASS] Exact Fit Buffer\n");
}

int	main(void)
{
	printf("=== Testing ft_strlcpy ===\n\n");

	test_normal_copy();
	test_truncation();
	test_zero_size();
	test_exact_fit();

	printf("\nAll ft_strlcpy tests passed successfully!\n");
	return (0);
}