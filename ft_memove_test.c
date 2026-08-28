
#include <stdio.h>
#include <string.h>
#include <assert.h>

static void	test_forward_overlap(void)
{
	// Case 1: dest > src (dst is shifted forward into src)
	// Must copy BACKWARDS to avoid overwriting unread source data.
	char	buffer1[] = "1234567890";
	char	buffer2[] = "1234567890";

	// Shift "12345" 2 positions to the right -> index 2 ("1231234590")
	memmove(buffer1 + 2, buffer1, 5);
	ft_memmove(buffer2 + 2, buffer2, 5);

	assert(memcmp(buffer1, buffer2, sizeof(buffer1)) == 0);
	printf("[PASS] Forward Overlap (dest > src)\n");
}

static void	test_backward_overlap(void)
{
	// Case 2: dest < src (dst is shifted backward into src)
	// Standard FORWARD copy works fine here.
	char	buffer1[] = "1234567890";
	char	buffer2[] = "1234567890";

	// Shift "34567" 2 positions to the left -> index 0 ("3456767890")
	memmove(buffer1, buffer1 + 2, 5);
	ft_memmove(buffer2, buffer2 + 2, 5);

	assert(memcmp(buffer1, buffer2, sizeof(buffer1)) == 0);
	printf("[PASS] Backward Overlap (dest < src)\n");
}

static void	test_no_overlap(void)
{
	char	src[] = "Hello 42!";
	char	dst1[20] = {0};
	char	dst2[20] = {0};

	memmove(dst1, src, strlen(src) + 1);
	ft_memmove(dst2, src, strlen(src) + 1);

	assert(memcmp(dst1, dst2, sizeof(dst1)) == 0);
	printf("[PASS] Non-Overlapping Copy\n");
}

static void	test_edge_cases(void)
{
	char	buf[] = "Edge Case";

	// Zero length copy
	ft_memmove(buf, buf + 2, 0);
	assert(strcmp(buf, "Edge Case") == 0);

	// Both NULL with 0 size (Libft requirement)
	assert(ft_memmove(NULL, NULL, 0) == NULL);

	printf("[PASS] Edge Cases (0-byte and NULL pointers)\n");
}

int	main(void)
{
	printf("=== Testing ft_memmove ===\n\n");

	test_forward_overlap();
	test_backward_overlap();
	test_no_overlap();
	test_edge_cases();

	printf("\nAll tests passed successfully!\n");
	return (0);
}