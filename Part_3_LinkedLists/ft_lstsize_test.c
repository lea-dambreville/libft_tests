#include <stdio.h>
#include <stdlib.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// // Function prototypes
// t_list	*ft_lstnew(void *content);
// int		ft_lstsize(t_list *lst);

// Custom non-terminating assertion macro[cite: 1, 2]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Helper function to safely free allocated nodes
static void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	test_ft_lstsize(void)
{
	printf("--- Testing ft_lstsize ---\n");

	// 1. Empty List (NULL Pointer)
	{
		t_list	*head = NULL;

		TEST_ASSERT("Empty list (NULL head) returns size 0", ft_lstsize(head) == 0);
	}

	// 2. Single Node List
	{
		t_list	*node1 = ft_lstnew("Node 1");

		TEST_ASSERT("Single node list returns size 1", ft_lstsize(node1) == 1);
		free_list(node1);
	}

	// 3. Multi-Node List
	{
		t_list	*node1 = ft_lstnew("Node 1");
		t_list	*node2 = ft_lstnew("Node 2");
		t_list	*node3 = ft_lstnew("Node 3");

		node1->next = node2;
		node2->next = node3;

		TEST_ASSERT("Three-node list returns size 3", ft_lstsize(node1) == 3);
		free_list(node1);
	}

	// 4. Large Linked List
	{
		t_list	*head = NULL;
		t_list	*curr = NULL;
		int		total_nodes = 100;

		for (int i = 0; i < total_nodes; i++)
		{
			t_list *new_node = ft_lstnew("Data");
			if (!head)
			{
				head = new_node;
				curr = head;
			}
			else
			{
				curr->next = new_node;
				curr = curr->next;
			}
		}

		TEST_ASSERT("100-node list returns size 100", ft_lstsize(head) == 100);
		free_list(head);
	}
}

int	main(void)
{
	test_ft_lstsize();
	return (0);
}