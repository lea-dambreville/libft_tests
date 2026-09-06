#include <stdio.h>
#include <stdlib.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function prototypes
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);

// Custom non-terminating assertion macro[cite: 2, 3]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Helper function to free list memory
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

void	test_ft_lstlast(void)
{
	printf("--- Testing ft_lstlast ---\n");

	// 1. Empty List (NULL Input)
	{
		t_list	*head = NULL;

		TEST_ASSERT("Empty list (NULL head) returns NULL", ft_lstlast(head) == NULL);
	}

	// 2. Single Node List
	{
		t_list	*node1 = ft_lstnew("Only Node");

		TEST_ASSERT("Single node list returns the node itself", ft_lstlast(node1) == node1);
		free_list(node1);
	}

	// 3. Multi-Node List
	{
		t_list	*node1 = ft_lstnew("First");
		t_list	*node2 = ft_lstnew("Second");
		t_list	*node3 = ft_lstnew("Last Node");

		node1->next = node2;
		node2->next = node3;

		TEST_ASSERT("Returns pointer to the last node", ft_lstlast(node1) == node3);
		TEST_ASSERT("Last node content matches", strcmp((char *)ft_lstlast(node1)->content, "Last Node") == 0);
		TEST_ASSERT("Last node next pointer is NULL", ft_lstlast(node1)->next == NULL);

		free_list(node1);
	}

	// 4. Sub-list Traversal
	{
		t_list	*node1 = ft_lstnew("Node 1");
		t_list	*node2 = ft_lstnew("Node 2");
		t_list	*node3 = ft_lstnew("Node 3");

		node1->next = node2;
		node2->next = node3;

		TEST_ASSERT("Starting search from second node still finds last node", ft_lstlast(node2) == node3);

		free_list(node1);
	}
}

int	main(void)
{
	test_ft_lstlast();
	return (0);
}