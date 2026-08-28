
#include <stdio.h>
void test_char(char c, int expected)
{
    int result = ft_isalpha(c);
    if (result == expected)
    {
        printf("[PASS] Character '%c' (ASCII %d) 
-> Got: %d\n", c, c, result);
    }
    else
    {
        printf("[FAIL] Character '%c' (ASCII %d) -> 
Expected: %d, Got: %d\n", c, c, expected, result);
    }
}

int main(void)
{
    printf("--- Running ft_isalpha tests ---\n");

    // Test Lowercase
    test_char('a', 1); // Lowercase boundary start
    test_char('m', 1); // Lowercase middle
    test_char('z', 1); // Lowercase boundary end

    // Test Uppercase
    test_char('A', 1); // Uppercase boundary start
    test_char('Q', 1); // Uppercase middle
    test_char('Z', 1); // Uppercase boundary end

    // Test Non-Alphabetic Characters
    test_char('0', 0); // Digit
    test_char('9', 0); // Digit
    test_char(' ', 0); // Space
    test_char('!', 0); // Punctuation
    test_char('\n', 0); // Control character

    // Test ASCII Boundary Conditions (characters right next to letters)
    test_char('`', 0); // ASCII 96 (one before 'a')
    test_char('{', 0); // ASCII 123 (one after 'z')
    test_char('@', 0); // ASCII 64 (one before 'A')
    test_char('[', 0); // ASCII 91 (one after 'Z')

    return (0);
}

Mini test
#include <stdio.h>
int main()
{
    printf("%d\n", ft_isalpha('b'));
    printf("%d\n", ft_isalpha('*'));
    return (0);
}