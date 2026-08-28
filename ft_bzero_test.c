#include <stdio.h>
#include <string.h>

/* Helper function to check if a memory block is entirely zeros */
int is_zeroed(unsigned char *m, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		if (m[i] != 0)
			return (0); /* Fail: found a non-zero byte */
		i++;
	}
	return (1); /* Pass: all bytes are zero */
}

int main(void)
{
	int test_num = 1;

	printf("--- STARTING FT_BZERO TESTS ---\n\n");

	/* Test 1: Basic String Zeroing */
	{
		char str[] = "Hello!";
		/* Zero out the first 4 bytes ("Hell") */
		ft_bzero(str, 4);
		
		if (is_zeroed((unsigned char *)str, 4) && str[4] == 'o' && str[5] == '!')
			printf("Test %d: PASS (Basic string partial zeroing)\n", test_num++);
		else
			printf("Test %d: FAIL (Basic string partial zeroing)\n", test_num++);
	}

	/* Test 2: Full Buffer Zeroing */
	{
		char buf[5] = {1, 2, 3, 4, 5};
		ft_bzero(buf, 5);

		if (is_zeroed((unsigned char *)buf, 5))
			printf("Test %d: PASS (Full buffer zeroing)\n", test_num++);
		else
			printf("Test %d: FAIL (Full buffer zeroing)\n", test_num++);
	}

	/* Test 3: Count is 0 (Edge Case) */
	{
		char buf[5] = {42, 42, 42, 42, 42};
		size_t zero_size = 0;

		ft_bzero(buf, zero_size);

		/* The buffer should remain completely untouched */
		if (buf[0] == 42 && buf[1] == 42 && buf[2] == 42 && buf[3] == 42 && buf[4] == 42)
			printf("Test %d: PASS (Count is 0 edge case)\n", test_num++);
		else
			printf("Test %d: FAIL (Count is 0 edge case)\n", test_num++);
	}

	printf("\n--- TESTS COMPLETE ---\n");
	return (0);
}