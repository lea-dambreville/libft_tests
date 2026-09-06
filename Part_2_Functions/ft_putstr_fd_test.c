#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Non-terminating test assertion macro[cite: 1]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_putstr_fd(void)
{
	printf("--- Testing ft_putstr_fd ---\n");

	// 1. Standard String Output
	{
		const char	*filename = "test_putstr_basic.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putstr_fd("Hello, 42!", fd);
			close(fd);

			// Read back from file to verify contents
			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write standard string to file descriptor",
				bytes_read == 10 && strcmp(buf, "Hello, 42!") == 0);
			remove(filename);
		}
	}

	// 2. Output String with Newlines and Special Characters
	{
		const char	*filename = "test_putstr_special.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putstr_fd("Line 1\nLine 2\tEnd", fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write string containing newline and tab",
				strcmp(buf, "Line 1\nLine 2\tEnd") == 0);
			remove(filename);
		}
	}

	// 3. Empty String Processing
	{
		const char	*filename = "test_putstr_empty.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putstr_fd("", fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[10] = {'X'};
			ssize_t bytes_read = read(fd, buf, sizeof(buf));
			close(fd);

			TEST_ASSERT("Empty string writes 0 bytes", bytes_read == 0);
			remove(filename);
		}
	}

	// 4. NULL String Guard Check (if implemented)
	{
		// Should execute safely without crashing when given a NULL pointer
		ft_putstr_fd(NULL, 1);
		TEST_ASSERT("NULL string input safety (no crash)", 1);
	}

	// 5. Invalid File Descriptor Guard Check
	{
		// Should execute safely without crashing when given an invalid FD
		ft_putstr_fd("Test", -1);
		TEST_ASSERT("Invalid file descriptor safety (-1)", 1);
	}
}

int	main(void)
{
	test_ft_putstr_fd();
	return (0);
}