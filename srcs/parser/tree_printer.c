/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:07:11 by marnaudy          #+#    #+#             */
/*   Updated: 2022/05/12 11:54:22 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	do_nothing(void *something)
{
	(void) something;
}

void	void_puts(void *str)
{
	puts((char *) str);
}

void	print_node(t_tree *node)
{
	int		i;

	printf("\n_________________________\n");
	printf("node type = %i\n", node->type);
	printf("Args =\n");
	ft_lstiter(node->arg, &void_puts);
	printf("infile = _%s_, outfile = _%s_, append = %i\n", node->infile, node->outfile, node->append_output);
	if (node->here_doc)
		printf("heredoc = _%s_, is quoted = %i\n", (char *)node->here_doc->content, node->here_doc->is_quoted);
	if (node->left)
		printf("Left node type = %i, arg0 = _%s_\n", node->left->type, node->left->arg ? (char *)node->left->arg->content : "empty");
	else
		printf("No left node\n");
	if (node->right)
		printf("Right node type = %i, arg0 = _%s_\n", node->right->type, node->right->arg ? (char *)node->right->arg->content : "empty");
	else
		printf("No right node\n");
	if (!node->pipe_children)
		return ;
	i = 0;
	while (node->pipe_children[i])
	{
		printf("Child n %i, type = %i, arg0 = _%s_\n", i, node->pipe_children[i]->type, node->pipe_children[i]->arg ? (char *)node->pipe_children[i]->arg->content : "empty");
		i++;
	}
}

void	print_queue(t_list	**queue)
{
	t_tree	*node;
	t_list	*new;
	int		i;

	if (!(*queue))
		return ;
	node = (t_tree *)(*queue)->content;
	print_node(node);
	if (node->left)
	{
		new = ft_lstnew(node->left);
		ft_lstadd_back(queue, new);
	}
	if (node->right)
	{
		new = ft_lstnew(node->right);
		ft_lstadd_back(queue, new);
	}
	if (node->pipe_children)
	{
		i = 0;
		while (node->pipe_children[i])
		{
			new = ft_lstnew(node->pipe_children[i]);
			ft_lstadd_back(queue, new);
			i++;
		}
	}
	new = *queue;
	*queue = (*queue)->next;
	ft_lstdelone(new, &do_nothing);
	print_queue(queue);
}

void	print_tree(t_tree *tree)
{
	t_list	*queue;

	queue = ft_lstnew(tree);
	print_queue(&queue);
}
