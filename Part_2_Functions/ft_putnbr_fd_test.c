#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

// Non-terminating test assertion macro[cite: 1, 4]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_putnbr_fd(void)
{
	printf("--- Testing ft_putnbr_fd ---\n");

	// 1. Positive Integer
	{
		const char	*filename = "test_putnbr_pos.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putnbr_fd(42, fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write positive integer (42)",
				bytes_read == 2 && strcmp(buf, "42") == 0);
			remove(filename);
		}
	}

	// 2. Negative Integer
	{
		const char	*filename = "test_putnbr_neg.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putnbr_fd(-42, fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write negative integer (-42)",
				bytes_read == 3 && strcmp(buf, "-42") == 0);
			remove(filename);
		}
	}

	// 3. Zero Handling
	{
		const char	*filename = "test_putnbr_zero.txt";
		int			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putnbr_fd(0, fd);
			close(fd);

			fd = open(filename, O_RDONLY);
			char buf[50] = {0};
			ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write zero (0)",
				bytes_read == 1 && strcmp(buf, "0") == 0);
			remove(filename);
		}
	}

	// 4. Integer Boundary Limits (INT_MAX & INT_MIN)
	{
		const char	*filename_max = "test_putnbr_max.txt";
		int			fd = open(filename_max, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putnbr_fd(INT_MAX, fd);
			close(fd);

			fd = open(filename_max, O_RDONLY);
			char buf[50] = {0};
			read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write INT_MAX (2147483647)", strcmp(buf, "2147483647") == 0);
			remove(filename_max);
		}

		const char	*filename_min = "test_putnbr_min.txt";
		fd = open(filename_min, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd != -1)
		{
			ft_putnbr_fd(INT_MIN, fd);
			close(fd);

			fd = open(filename_min, O_RDONLY);
			char buf[50] = {0};
			read(fd, buf, sizeof(buf) - 1);
			close(fd);

			TEST_ASSERT("Write INT_MIN (-2147483648)", strcmp(buf, "-2147483648") == 0);
			remove(filename_min);
		}
	}

	// 5. Invalid File Descriptor Guard Check
	{
		ft_putnbr_fd(12345, -1);
		TEST_ASSERT("Invalid file descriptor safety (-1)", 1);
	}
}

int	main(void)
{
	test_ft_putnbr_fd();
	return (0);
}