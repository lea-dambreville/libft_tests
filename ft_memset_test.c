#include <stdio.h>
#include <string.h>

int verify_mem(unsigned char *m1, unsigned char *m2, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		if (m1[i] != m2[i])
			return (0); /* Fail */
		i++;
	}
	return (1); /* Pass */
}

int main(void)
{
	int test_num = 1;

	printf("--- STARTING FT_MEMSET TESTS ---\n\n");

	/* Test 1: Basic String Filling */
	{
		char str1[20] = "Hello World!";
		char str2[20] = "Hello World!";
		char *res1 = memset(str1, 'A', 5);
		char *res2 = ft_memset(str2, 'A', 5);
		
		if (verify_mem((unsigned char *)str1, (unsigned char *)str2, 20) && res1 == str1 && res2 == str2)
			printf("Test %d: PASS (Basic string fill)\n", test_num++);
		else
			printf("Test %d: FAIL (Basic string fill)\n", test_num++);
	}

	/* Test 2: Filling with Zero (bzero behavior) */
	{
		char buf1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		char buf2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		memset(buf1, 0, 6);
		ft_memset(buf2, 0, 6);

		if (verify_mem((unsigned char *)buf1, (unsigned char *)buf2, 10))
			printf("Test %d: PASS (Zero fill / bzero test)\n", test_num++);
		else
			printf("Test %d: FAIL (Zero fill / bzero test)\n", test_num++);
	}
    
    /* Test 3: Count is 0 (Edge Case) */
	{
		char str1[] = "KeepMe";
		char str2[] = "KeepMe";
		size_t zero_size = 0;

		memset(str1, 'X', zero_size);
		ft_memset(str2, 'X', zero_size);

		/* CHANGE THIS LINE FROM 10 TO 7 */
		if (verify_mem((unsigned char *)str1, (unsigned char *)str2, 7))
			printf("Test %d: PASS (Count is 0 edge case)\n", test_num++);
		else
			printf("Test %d: FAIL (Count is 0 edge case)\n", test_num++);
	}

	/* Test 4: Integer Overflow / Negative Int handling */
	/* memset expects an int but converts it internally to an unsigned char */
	{
		char buf1[5] = {1, 2, 3, 4, 5};
		char buf2[5] = {1, 2, 3, 4, 5};
		memset(buf1, 257, 3);    /* 257 becomes 1 as unsigned char */
		ft_memset(buf2, 257, 3);

		if (verify_mem((unsigned char *)buf1, (unsigned char *)buf2, 5))
			printf("Test %d: PASS (Int value overflow handling)\n", test_num++);
		else
			printf("Test %d: FAIL (Int value overflow handling)\n", test_num++);
	}

	printf("\n--- TESTS COMPLETE ---\n");
	return (0);
}
