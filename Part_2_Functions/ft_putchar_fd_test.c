#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// Prototype for ft_putchar_fd
void	ft_putchar_fd(char c, int fd);

// Non-terminating test assertion macro[cite: 1]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_putchar_fd(void)
{
	printf("--- Testing ft_putchar_fd ---\n");

	// 1. Output to a Temporary File Descriptor
	{
		const char	*filename = "test_putchar_out.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putchar_fd('A', fd);
			close(fd);

			// Read back from the file to verify content
			fd = open(filename, O_RDONLY);
			char read_char = 0;
			read(fd, &read_char, 1);
			close(fd);

			TEST_ASSERT("Write standard character ('A') to file descriptor", read_char == 'A');
			remove(filename);
		}
	}

	// 2. Output Special & Edge Characters
	{
		const char	*filename = "test_putchar_special.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putchar_fd('\n', fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char read_char = 0;
			read(fd, &read_char, 1);
			close(fd);

			TEST_ASSERT("Write newline character ('\\n') to file descriptor", read_char == '\n');
			remove(filename);
		}
	}

	// 3. Output Null Byte Character
	{
		const char	*filename = "test_putchar_null.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putchar_fd('\0', fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char read_char = 'X';
			ssize_t bytes_read = read(fd, &read_char, 1);
			close(fd);

			TEST_ASSERT("Write null byte ('\\0') writes 1 byte containing 0", bytes_read == 1 && read_char == '\0');
			remove(filename);
		}
	}

	// 4. Invalid File Descriptor Guard Check
	{
		// Should execute safely without crashing when given an invalid FD (-1)
		ft_putchar_fd('Z', -1);
		TEST_ASSERT("Invalid file descriptor safety (-1)", 1);
	}
}

int	main(void)
{
	test_ft_putchar_fd();
	return (0);
}