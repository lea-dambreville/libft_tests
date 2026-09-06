#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function prototype for ft_lstdelone
void	ft_lstdelone(t_list *lst, void (*del)(void *));

// Mock deletion functions
static int	g_del_called = 0;

static void	del_mock(void *content)
{
	if (content)
	{
		g_del_called++;
		free(content);
	}
}

static void	del_no_free_mock(void *content)
{
	(void)content;
	g_del_called++;
}

// Custom non-terminating assertion macro[cite: 2]
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

void	test_ft_lstdelone(void)
{
	printf("--- Testing ft_lstdelone ---\n");

	// 1. Basic Single Node Deletion (Memory Freed & del called)
	{
		g_del_called = 0;
		t_list *node = (t_list *)malloc(sizeof(t_list));
		char *content = strdup("Test Content");

		if (node && content)
		{
			node->content = content;
			node->next = NULL;

			ft_lstdelone(node, del_mock);
			TEST_ASSERT("del function called on node content", g_del_called == 1);
		}
	}

	// 2. Deleting Node with Static/Non-Allocated Content
	{
		g_del_called = 0;
		t_list *node = (t_list *)malloc(sizeof(t_list));

		if (node)
		{
			node->content = "Literal String";
			node->next = NULL;

			ft_lstdelone(node, del_no_free_mock);
			TEST_ASSERT("del function invoked without freeing static content", g_del_called == 1);
		}
	}

	// 3. Deleting Node with NULL Content
	{
		g_del_called = 0;
		t_list *node = (t_list *)malloc(sizeof(t_list));

		if (node)
		{
			node->content = NULL;
			node->next = NULL;

			ft_lstdelone(node, del_no_free_mock);
			TEST_ASSERT("Handles node with NULL content properly", g_del_called == 1);
		}
	}

	// 4. Detached List Isolation Check
	{
		g_del_called = 0;
		t_list *node1 = (t_list *)malloc(sizeof(t_list));
		t_list *node2 = (t_list *)malloc(sizeof(t_list));

		if (node1 && node2)
		{
			node1->content = strdup("Node 1");
			node2->content = strdup("Node 2");
			node1->next = node2;
			node2->next = NULL;

			// Delete only node1
			ft_lstdelone(node1, del_mock);
			TEST_ASSERT("Deletes targeted node without crashing next node", g_del_called == 1);

			// Clean up remaining node2 manually
			free(node2->content);
			free(node2);
		}
	}

	// 5. NULL Pointer Guard Checks
	{
		g_del_called = 0;
		t_list *node = (t_list *)malloc(sizeof(t_list));

		if (node)
		{
			node->content = NULL;
			node->next = NULL;

			ft_lstdelone(NULL, del_mock);
			TEST_ASSERT("NULL node safety (no crash)", g_del_called == 0);

			ft_lstdelone(node, NULL);
			TEST_ASSERT("NULL del function pointer safety (no crash)", g_del_called == 0);

			free(node);
		}
	}
}

int	main(void)
{
	test_ft_lstdelone();
	return (0);
}