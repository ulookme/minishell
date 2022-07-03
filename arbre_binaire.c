/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbre_binaire.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:42:47 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/03 13:48:19 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_binbash	*creat_node(void *content, t_binbash *prev)
{
	t_binbash	*node;

	node = (t_binbash *)malloc(sizeof(t_binbash));
	node->content = content;
	node->prev = prev;
	node->right = NULL;
	node->left = NULL;
	node->type = 0;
	return (node);
}

t_binbash	*arbre_decison_tree(t_binbash *node)
{
	char	**element;

	if (occurent(node->content, check_condition))
		element = ft_split_commande(node->content, check_condition);
	else if (occurent(node->content, check_pipe))
		element = ft_split_commande(node->content, check_pipe);
	else if (occurent(node->content, check_redirection))
		element = ft_split_commande(node->content, check_redirection);
	else
	{
		node->content = (void *) ft_split_arg(node->content);
		return (node);
	}
	node->type = 1;
	node->content = element[1];
	node->left = arbre_decison_tree(creat_node(element[0], node));
	node->right = arbre_decison_tree(creat_node(element[2], node));
	free(element);
	return (node);
}

void	display_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		ft_printf("%s ", args[i++]);
	ft_printf("\n");
}

void	display_tree(t_binbash *node, int depth)
{
	int		i;

	if (!node)
		return ;
	i = 0;
	while (i < depth)
	{
		if (i++ == depth - 1)
			ft_printf("| >>\t");
		else
			ft_printf("|\t");
	}
	if (node->type)
		ft_printf("%s\n", node->content);
	else
		display_args((char **) node->content);
	display_tree(node->left, depth + 1);
	display_tree(node->right, depth + 1);
}
