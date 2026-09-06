#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of t_list node structure for Libft bonus part
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Custom non-terminating assertion macro[cite: 2, 3]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_lstnew(void)
{
	printf("--- Testing ft_lstnew ---\n");

	// 1. Node Creation with String Content
	{
		char	*content = "Hello 42";
		t_list	*node = ft_lstnew(content);

		TEST_ASSERT("Node pointer is non-NULL", node != NULL);
		TEST_ASSERT("Node content points to string address", node != NULL && node->content == content);
		TEST_ASSERT("Node next pointer initialized to NULL", node != NULL && node->next == NULL);
		free(node);
	}

	// 2. Node Creation with Integer Content
	{
		int		val = 42;
		t_list	*node = ft_lstnew(&val);

		TEST_ASSERT("Node content stores integer pointer correctly", node != NULL && *(int *)(node->content) == 42);
		TEST_ASSERT("Node next is NULL", node != NULL && node->next == NULL);
		free(node);
	}

	// 3. Node Creation with Heap Memory Content
	{
		int	*heap_val = (int *)malloc(sizeof(int));
		if (heap_val)
		{
			*heap_val = 100;
			t_list	*node = ft_lstnew(heap_val);

			TEST_ASSERT("Node stores heap-allocated address", node != NULL && node->content == heap_val);
			free(heap_val);
			free(node);
		}
	}

	// 4. Node Creation with NULL Content
	{
		t_list	*node = ft_lstnew(NULL);

		TEST_ASSERT("Node pointer is non-NULL when content is NULL", node != NULL);
		TEST_ASSERT("Node content is NULL", node != NULL && node->content == NULL);
		TEST_ASSERT("Node next pointer is NULL", node != NULL && node->next == NULL);
		free(node);
	}
}

int	main(void)
{
	test_ft_lstnew();
	return (0);
}