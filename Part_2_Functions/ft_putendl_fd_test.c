#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Non-terminating test assertion macro[cite: 1, 4]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_putendl_fd(void)
{
	printf("--- Testing ft_putendl_fd ---\n");

	// 1. Standard String Output with Appended Newline
	{
		const char	*filename = "test_putendl_basic.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putendl_fd("Hello, 42!", fd);
			close(fd);

			// Read back from file to verify string and appending newline
			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write standard string with appended newline '\\n'",
				bytes_read == 11 && strcmp(buf, "Hello, 42!\n") == 0);
			remove(filename);
		}
	}

	// 2. Output Multi-line / Special Characters String
	{
		const char	*filename = "test_putendl_special.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putendl_fd("Line 1\tEnd", fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write string with internal tab and appended newline",
				strcmp(buf, "Line 1\tEnd\n") == 0);
			remove(filename);
		}
	}

	// 3. Empty String Input
	{
		const char	*filename = "test_putendl_empty.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putendl_fd("", fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[10] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Empty string input writes exactly 1 byte ('\\n')",
				bytes_read == 1 && strcmp(buf, "\n") == 0);
			remove(filename);
		}
	}

	// 4. NULL String Guard Check (if implemented)
	{
		// Should execute safely without crashing when given a NULL pointer
		ft_putendl_fd(NULL, 1);
		TEST_ASSERT("NULL string input safety (no crash)", 1);
	}

	// 5. Invalid File Descriptor Guard Check
	{
		// Should execute safely without crashing when given an invalid FD
		ft_putendl_fd("Test", -1);
		TEST_ASSERT("Invalid file descriptor safety (-1)", 1);
	}
}

int	main(void)
{
	test_ft_putendl_fd();
	return (0);
}