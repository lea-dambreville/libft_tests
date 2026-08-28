#include <stdio.h>
#include <ctype.h>

// Helper function to evaluate and print test results
void test_char(int c, const char *description) {
	int expected = (isascii(c) != 0); 
// Convert standard library truthy to 1
	int actual = ft_isascii(c);

	if (expected == actual) {
		printf("[ PASS ] %-20s (Input: %4d) 
-> Got: %d\n", description, c, actual);
	} else {
		printf("[ FAIL ] %-20s (Input: %4d) 
-> Expected: %d, Got: %d\n", description, c, expected, actual);
	}
}

int main() {
	printf("=== Running ft_isascii tests ===\n\n");

	// 1. Boundary Tests (Valid ASCII Edges)
	test_char(0, "Lower bound (NUL)");
	test_char(127, "Upper bound (DEL)");

	// 2. Mid-range Valid ASCII Tests
	test_char(65, "Uppercase 'A'");
	test_char(97, "Lowercase 'a'");
	test_char(10, "Newline '\\n'");
	test_char(32, "Space ' '");

	// 3. Out-of-bounds Boundaries (Invalid ASCII)
	test_char(128, "Just past upper bound");
	test_char(255, "Max 8-bit unsigned val");

	// 4. Large Integer Tests (Validating the bitwise mask scales)
	test_char(129, "Value 129");
	test_char(1000, "Large positive number");

	// 5. Negative Value Tests (Handling signed chars / EOF)
	test_char(-1, "EOF marker (-1)");
	test_char(-128, "Negative boundary");

	// 6. Comprehensive Loop Test 
// (Quick sanity check of entire basic 0-255 byte spectrum)
	int failures = 0;
	for (int i = 0; i <= 255; i++) {
		int exp = (isascii(i) != 0);
		if (ft_isascii(i) != exp) {
			failures++;
		}
	}
	printf("\nLoop validation (0-255): 
%s (%d failures)\n", failures == 0 ? "SUCCESS" : "FAILED", failures);

	return 0;
}