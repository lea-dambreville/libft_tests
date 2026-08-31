#include <stdio.h>
#include <string.h>
#include <assert.h>
#define TEST_ASSERT(test_name, condition) \
    do { \
        if (condition) { \
            printf("[PASS] %s\n", test_name); \
        } else { \
            printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
        } \
    } while (0)
void test_ft_memcmp(void)
{
    printf("--- Testing ft_memcmp ---\n");
    TEST_ASSERT("Identical memory blocks", ft_memcmp("abc", "abc", 3) == 0);
    TEST_ASSERT("Difference at byte index 2", ft_memcmp("abc", "abd", 3) < 0);
    TEST_ASSERT("Byte difference after null byte", ft_memcmp("a\0b", "a\0c", 3) < 0);
    TEST_ASSERT("Zero length compare", ft_memcmp("abc", "xyz", 0) == 0);
    
    // Unsigned char comparison test
    unsigned char buf1[] = {0xFF, 0x00};
    unsigned char buf2[] = {0x01, 0x00};
    TEST_ASSERT("Unsigned char cast evaluation", ft_memcmp(buf1, buf2, 2) > 0);
    printf("\n");
}
int main(void)
{
    test_ft_memcmp();
    return (0);
}