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
void	ft_lstadd_front(t_list **lst, t_list *new_node);

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Helper function to free list nodes
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

void	test_ft_lstadd_front(void)
{
	printf("--- Testing ft_lstadd_front ---\n");

	// 1. Prepend Node to Empty List (*lst == NULL)
	{
		t_list	*head = NULL;
		t_list	*node1 = ft_lstnew("First Node");

		ft_lstadd_front(&head, node1);
		TEST_ASSERT("Head points to newly added node", head == node1);
		TEST_ASSERT("Head content matches", head != NULL && strcmp((char *)head->content, "First Node") == 0);
		TEST_ASSERT("Head next is NULL", head != NULL && head->next == NULL);

		free_list(head);
	}

	// 2. Prepend Node to Existing List
	{
		t_list	*head = ft_lstnew("Old Head");
		t_list	*new_head = ft_lstnew("New Head");

		ft_lstadd_front(&head, new_head);

		TEST_ASSERT("Head is updated to new node", head == new_head);
		TEST_ASSERT("New head next points to old head", head != NULL && head->next != NULL && strcmp((char *)head->next->content, "Old Head") == 0);

		free_list(head);
	}

	// 3. Chain Multiple Insertions
	{
		t_list	*head = NULL;
		t_list	*node1 = ft_lstnew("Node 1");
		t_list	*node2 = ft_lstnew("Node 2");
		t_list	*node3 = ft_lstnew("Node 3");

		ft_lstadd_front(&head, node1);
		ft_lstadd_front(&head, node2);
		ft_lstadd_front(&head, node3);

		TEST_ASSERT("Node 3 is head", head == node3);
		TEST_ASSERT("Node 3 next is Node 2", head != NULL && head->next == node2);
		TEST_ASSERT("Node 2 next is Node 1", head != NULL && head->next->next == node1);
		TEST_ASSERT("Node 1 next is NULL", head != NULL && head->next->next->next == NULL);

		free_list(head);
	}

	// 4. NULL Protection Safety
	{
		t_list	*head = ft_lstnew("Head");

		// Should safely do nothing when lst pointer or new_node is NULL
		ft_lstadd_front(NULL, head);
		TEST_ASSERT("NULL list pointer safety (no crash)", 1);

		ft_lstadd_front(&head, NULL);
		TEST_ASSERT("NULL new node safety (list unchanged)", head != NULL && strcmp((char *)head->content, "Head") == 0);

		free_list(head);
	}
}

int	main(void)
{
	test_ft_lstadd_front();
	return (0);
}