#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function prototype for ft_lstclear
void	ft_lstclear(t_list **lst, void (*del)(void *));

// Custom non-terminating assertion macro[cite: 4]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Mock variables and functions for tracking deletions
static int	g_del_called = 0;

static void	del_mock(void *content)
{
	if (content)
	{
		g_del_called++;
		free(content);
	}
}

// Helper to quickly allocate test nodes
static t_list	*create_mock_node(const char *str)
{
	t_list	*node = (t_list *)malloc(sizeof(t_list));
	if (node)
	{
		node->content = strdup(str);
		node->next = NULL;
	}
	return (node);
}

void	test_ft_lstclear(void)
{
	printf("--- Testing ft_lstclear ---\n");

	// 1. Clear Multi-Node List
	{
		g_del_called = 0;
		t_list	*node1 = create_mock_node("Node 1");
		t_list	*node2 = create_mock_node("Node 2");
		t_list	*node3 = create_mock_node("Node 3");

		if (node1 && node2 && node3)
		{
			node1->next = node2;
			node2->next = node3;

			t_list *head = node1;
			ft_lstclear(&head, del_mock);

			TEST_ASSERT("del function called exactly 3 times for 3 nodes", g_del_called == 3);
			TEST_ASSERT("Head pointer is set to NULL after clearing", head == NULL);
		}
	}

	// 2. Clear Single Node List
	{
		g_del_called = 0;
		t_list	*head = create_mock_node("Single Node");

		if (head)
		{
			ft_lstclear(&head, del_mock);
			TEST_ASSERT("del function called exactly 1 time for single node", g_del_called == 1);
			TEST_ASSERT("Head pointer is set to NULL", head == NULL);
		}
	}

	// 3. Empty List (Pointer to NULL)
	{
		g_del_called = 0;
		t_list	*head = NULL;

		ft_lstclear(&head, del_mock);
		TEST_ASSERT("Safe execution when clearing an already empty list", g_del_called == 0);
		TEST_ASSERT("Head pointer remains NULL", head == NULL);
	}

	// 4. NULL Double Pointer Guard
	{
		g_del_called = 0;
		// Should execute safely without crashing when the list pointer itself is NULL
		ft_lstclear(NULL, del_mock);
		TEST_ASSERT("NULL double pointer (**lst) safety (no crash)", g_del_called == 0);
	}
}

int	main(void)
{
	test_ft_lstclear();
	return (0);
}