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
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Custom non-terminating assertion macro
#define TEST_ASSERT(test_name, condition) \
	do { \
		if (condition) { \
			printf("[PASS] %s\n", test_name); \
		} else { \
			printf("[FAIL] %s (Line %d)\n", test_name, __LINE__); \
		} \
	} while (0)

// Helper tracking variables and functions
static int	g_f_called = 0;
static int	g_del_called = 0;

static void	*duplicate_and_uppercase(void *content)
{
	if (!content)
		return (NULL);

	g_f_called++;
	char *str = strdup((char *)content);
	if (!str)
		return (NULL);

	for (int i = 0; str[i]; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
	return (str);
}

static void	*f_fail_on_third(void *content)
{
	g_f_called++;
	if (g_f_called == 3)
		return (NULL); // Simulate allocation failure on 3rd node
	return (strdup((char *)content));
}

static void	del_mock(void *content)
{
	if (content)
	{
		g_del_called++;
		free(content);
	}
}

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

void	test_ft_lstmap(void)
{
	printf("--- Testing ft_lstmap ---\n");

	// 1. Standard Transformation and Deep Copying
	{
		g_f_called = 0;
		g_del_called = 0;

		t_list *n1 = ft_lstnew("alpha");
		t_list *n2 = ft_lstnew("beta");
		t_list *n3 = ft_lstnew("gamma");

		n1->next = n2;
		n2->next = n3;

		t_list *mapped = ft_lstmap(n1, duplicate_and_uppercase, del_mock);

		TEST_ASSERT("Mapping executed on all 3 nodes", g_f_called == 3);
		TEST_ASSERT("New list head created", mapped != NULL && mapped != n1);
		TEST_ASSERT("Node 1 content transformed ('ALPHA')", mapped != NULL && strcmp((char *)mapped->content, "ALPHA") == 0);
		TEST_ASSERT("Node 2 content transformed ('BETA')", mapped != NULL && mapped->next && strcmp((char *)mapped->next->content, "BETA") == 0);
		TEST_ASSERT("Node 3 content transformed ('GAMMA')", mapped != NULL && mapped->next && mapped->next->next && strcmp((char *)mapped->next->next->content, "GAMMA") == 0);
		TEST_ASSERT("Original list content remains unmodified ('alpha')", strcmp((char *)n1->content, "alpha") == 0);

		free(n1); free(n2); free(n3);
		free_list(mapped);
	}

	// 2. Memory Allocation Failure Cleanup (Rollback Test)
	{
		g_f_called = 0;
		g_del_called = 0;

		t_list *n1 = ft_lstnew("one");
		t_list *n2 = ft_lstnew("two");
		t_list *n3 = ft_lstnew("three");
		t_list *n4 = ft_lstnew("four");

		n1->next = n2;
		n2->next = n3;
		n3->next = n4;

		t_list *mapped = ft_lstmap(n1, f_fail_on_third, del_mock);

		TEST_ASSERT("Returns NULL when middle node allocation fails", mapped == NULL);
		TEST_ASSERT("Previously allocated nodes freed via del function", g_del_called == 2);

		free(n1); free(n2); free(n3); free(n4);
	}

	// 3. Empty Input List (NULL Head)
	{
		g_f_called = 0;
		g_del_called = 0;

		t_list *mapped = ft_lstmap(NULL, duplicate_and_uppercase, del_mock);

		TEST_ASSERT("Empty list input returns NULL", mapped == NULL);
		TEST_ASSERT("Neither f nor del called", g_f_called == 0 && g_del_called == 0);
	}

	// 4. NULL Function Pointer Guards
	{
		t_list *n1 = ft_lstnew("test");

		t_list *res1 = ft_lstmap(n1, NULL, del_mock);
		TEST_ASSERT("NULL mapping function safety returns NULL", res1 == NULL);

		t_list *res2 = ft_lstmap(n1, duplicate_and_uppercase, NULL);
		TEST_ASSERT("NULL deletion function safety returns NULL", res2 == NULL);

		free(n1);
	}
}

int	main(void)
{
	test_ft_lstmap();
	return (0);
}