/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commande.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:49:03 by chajjar           #+#    #+#             */
/*   Updated: 2022/07/02 17:21:07 by chajjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*occurent(char *str, int (*condition)(char *))
{
	char	*ptr;
	int		quote;

	quote = 0;
	ptr = (char *)str;
	while (*ptr != '\0')
	{
		check_quote(*ptr, &quote);
		if (!quote && condition(ptr))
			return (ptr);
		ptr++;
	}
	return (NULL);
}

static char	**ft_alloc_element(
	char **element, char *str, int (*condition)(char *))
{
	size_t	len;
	size_t	len2;

	len2 = 0;
	if (occurent(str, condition))
		len2 = ft_strlen(occurent(str, condition));
	len = ft_strlen(str) - len2;
	if (len)
	{
		element[0] = ft_calloc(len, sizeof(char));
		ft_strlcpy(element[0], str, len + 1);
	}
	if (condition(&str[len]))
	{
		element[1] = ft_calloc(condition(&str[len]), sizeof(char));
		ft_strlcpy(element[1], &str[len], condition(&str[len]) + 1);
	}
	if (len2)
	{
		element[2] = ft_calloc(len2, sizeof(char));
		ft_strlcpy(element[2], &str[len + condition(&str[len])], len2 + 1);
	}
	return (element);
}

// void	ft_input_element(char **element, char *str, int (*condition)(char *))
// {
// 	int	quote;
// 	int	index;
// 	int numb_elem;

// 	index = 0;
// 	numb_elem = 0;
// 	quote = 0;
// 	while (*str && str[index])
// 	{
// 		if (&str[index] == occurent(str, condition))
// 			index += condition(str);
// 	}	
// }

char	**ft_split_commande(char *str, int (*condition)(char *))
{
	char	**element;

	element = ft_calloc(4, sizeof(char *));
	if (element)
		element = ft_alloc_element(element, str, condition);
	return (element);
}
