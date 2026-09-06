#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of t_list node structure for Libft
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function prototype for ft_lstiter
void	ft_lstiter(t_list *lst, void (*f)(void *));

// Mock iteration callbacks and state tracking
static int	g_apply_count = 0;

static void	uppercase_content(void *content)
{
	if (!content)
		return ;
	
	char *str = (char *)content;
	g_apply_count++;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Helper function to create dynamically allocated mock nodes
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

// Helper function to free list memory
static void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->content)
			free(head->content);
		free(head);
		head = tmp;
	}
}

void	test_ft_lstiter(void)
{
	printf("--- Testing ft_lstiter ---\n");

	// 1. Traverse and Modify Multi-Node List
	{
		g_apply_count = 0;
		t_list	*node1 = create_mock_node("first");
		t_list	*node2 = create_mock_node("second");
		t_list	*node3 = create_mock_node("third");

		if (node1 && node2 && node3)
		{
			node1->next = node2;
			node2->next = node3;

			ft_lstiter(node1, uppercase_content);

			TEST_ASSERT("Callback applied to all 3 nodes", g_apply_count == 3);
			TEST_ASSERT("Node 1 content modified ('FIRST')", strcmp((char *)node1->content, "FIRST") == 0);
			TEST_ASSERT("Node 2 content modified ('SECOND')", strcmp((char *)node2->content, "SECOND") == 0);
			TEST_ASSERT("Node 3 content modified ('THIRD')", strcmp((char *)node3->content, "THIRD") == 0);

			free_list(node1);
		}
	}

	// 2. Single Node Iteration
	{
		g_apply_count = 0;
		t_list	*head = create_mock_node("hello");

		if (head)
		{
			ft_lstiter(head, uppercase_content);

			TEST_ASSERT("Callback applied exactly once for single node", g_apply_count == 1);
			TEST_ASSERT("Single node content updated ('HELLO')", strcmp((char *)head->content, "HELLO") == 0);

			free_list(head);
		}
	}

	// 3. Empty List (NULL Pointer)
	{
		g_apply_count = 0;
		t_list	*head = NULL;

		ft_lstiter(head, uppercase_content);

		TEST_ASSERT("Empty list executes without invoking callback", g_apply_count == 0);
	}

	// 4. NULL Function Pointer Safety (if implemented in your code)
	{
		t_list	*head = create_mock_node("test");

		if (head)
		{
			ft_lstiter(head, NULL);
			TEST_ASSERT("NULL function pointer safety (no crash, content unchanged)", strcmp((char *)head->content, "test") == 0);

			free_list(head);
		}
	}
}

int	main(void)
{
	test_ft_lstiter();
	return (0);
}