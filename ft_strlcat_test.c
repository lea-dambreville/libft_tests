#include <stdio.h>
#include <string.h>

// Custom assert macro that tracks test names and prints PASS / FAIL
#define TEST_ASSERT(test_name, condition) \
    do { \
        if (condition) { \
            printf("[PASS] %s\n", test_name); \
        } else { \
            printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
        } \
    } while (0)

void test_ft_strlcat(void)
{
    // Test 1: Basic concatenation with plenty of space
    {
        char buffer[20] = "Hello, ";
        size_t res = ft_strlcat(buffer, "World!", sizeof(buffer));
        TEST_ASSERT("Test 1 - Basic concatenation string match", strcmp(buffer, "Hello, World!") == 0);
        TEST_ASSERT("Test 1 - Basic concatenation return length", res == 13);
    }

    // Test 2: Truncation
    {
        char buffer[10] = "Hello, ";
        size_t res = ft_strlcat(buffer, "World!", sizeof(buffer));
        TEST_ASSERT("Test 2 - Truncated string match", strcmp(buffer, "Hello, Wo") == 0);
        TEST_ASSERT("Test 2 - Truncated return length", res == 13);
    }

    // Test 3: dstsize is 0
    {
        char buffer[10] = "Hello";
        size_t res = ft_strlcat(buffer, "World", 0);
        TEST_ASSERT("Test 3 - dstsize 0 buffer untouched", strcmp(buffer, "Hello") == 0);
        TEST_ASSERT("Test 3 - dstsize 0 return value", res == 5);
    }

    // Test 4: dstsize smaller than initial dest length
    {
        char buffer[10] = "Hello";
        size_t res = ft_strlcat(buffer, "World", 3);
        TEST_ASSERT("Test 4 - dstsize < dest_len buffer untouched", strcmp(buffer, "Hello") == 0);
        TEST_ASSERT("Test 4 - dstsize < dest_len return value", res == 8);
    }

    // Test 5: dstsize equals initial dest length
    {
        char buffer[10] = "Hello";
        size_t res = ft_strlcat(buffer, "World", 5);
        TEST_ASSERT("Test 5 - dstsize == dest_len buffer untouched", strcmp(buffer, "Hello") == 0);
        TEST_ASSERT("Test 5 - dstsize == dest_len return value", res == 10);
    }

    // Test 6: Appending empty string
    {
        char buffer[10] = "Hello";
        size_t res = ft_strlcat(buffer, "", sizeof(buffer));
        TEST_ASSERT("Test 6 - Empty src string match", strcmp(buffer, "Hello") == 0);
        TEST_ASSERT("Test 6 - Empty src return value", res == 5);
    }

    // Test 7: Appending to empty destination
    {
        char buffer[10] = "";
        size_t res = ft_strlcat(buffer, "Hello", sizeof(buffer));
        TEST_ASSERT("Test 7 - Empty dest string match", strcmp(buffer, "Hello") == 0);
        TEST_ASSERT("Test 7 - Empty dest return value", res == 5);
    }
}

int main(void)
{
    test_ft_strlcat();
    return (0);
}