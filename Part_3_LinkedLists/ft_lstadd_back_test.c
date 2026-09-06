#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function prototypes
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new_node);

// Custom non-terminating assertion macro
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

void	test_ft_lstadd_back(void)
{
	printf("--- Testing ft_lstadd_back ---\n");

	// 1. Append Node to Empty List (*lst == NULL)
	{
		t_list	*head = NULL;
		t_list	*node1 = ft_lstnew("First Node");

		ft_lstadd_back(&head, node1);
		TEST_ASSERT("Head points to newly added node", head == node1);
		TEST_ASSERT("Head content matches", head != NULL && strcmp((char *)head->content, "First Node") == 0);
		TEST_ASSERT("Head next is NULL", head != NULL && head->next == NULL);

		free_list(head);
	}

	// 2. Append Node to Existing Single-Node List
	{
		t_list	*head = ft_lstnew("Head Node");
		t_list	*node_back = ft_lstnew("Tail Node");

		ft_lstadd_back(&head, node_back);

		TEST_ASSERT("Head remains unchanged", head != NULL && strcmp((char *)head->content, "Head Node") == 0);
		TEST_ASSERT("Head next points to back node", head != NULL && head->next == node_back);
		TEST_ASSERT("Tail node next is NULL", head != NULL && head->next->next == NULL);

		free_list(head);
	}

	// 3. Chain Multiple Insertions (Preserves FIFO Order)
	{
		t_list	*head = NULL;
		t_list	*node1 = ft_lstnew("Node 1");
		t_list	*node2 = ft_lstnew("Node 2");
		t_list	*node3 = ft_lstnew("Node 3");

		ft_lstadd_back(&head, node1);
		ft_lstadd_back(&head, node2);
		ft_lstadd_back(&head, node3);

		TEST_ASSERT("Head is Node 1", head == node1);
		TEST_ASSERT("Node 1 next is Node 2", head != NULL && head->next == node2);
		TEST_ASSERT("Node 2 next is Node 3", head != NULL && head->next->next == node3);
		TEST_ASSERT("Node 3 next is NULL", head != NULL && head->next->next->next == NULL);

		free_list(head);
	}

	// 4. NULL Protection Safety
	{
		t_list	*head = ft_lstnew("Head");

		// Should safely handle NULL list pointer or NULL new_node without crashing
		ft_lstadd_back(NULL, head);
		TEST_ASSERT("NULL list pointer safety (no crash)", 1);

		ft_lstadd_back(&head, NULL);
		TEST_ASSERT("NULL new node safety (list unchanged)", head != NULL && head->next == NULL);

		free_list(head);
	}
}

int	main(void)
{
	test_ft_lstadd_back();
	return (0);
}