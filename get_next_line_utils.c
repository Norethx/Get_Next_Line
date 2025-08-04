/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:03:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/08/04 12:08:16 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_cleanls(t_list **lst, int t_clean)
{
	t_list	*aux;

	aux = *lst;
	if (*lst && t_clean == 0)
	{
		free(aux->content);
		free(aux);
	}
	else if (*lst && t_clean == 1)
	{
		while (*lst)
		{
			aux = *lst;
			*lst = aux->next;
			free(aux->content);
			free(aux);
		}
		aux = NULL;
		*lst = aux;
	}
	return ((void *)0);
}

void	ft_lst_content_substr(t_list **lst, int loc)
{
	int		i;
	char	*new_str;
	t_list	*aux;

	i = 0;
	aux = *lst;
	while (((char *)aux->content)[i] != 0)
		i++;
	new_str = malloc((i - loc) + 1);
	new_str[i - loc] = 0;
	i = 0;
	while (((char *)aux->content)[i + loc] != 0)
	{
		new_str[i] = ((char *)aux->content)[i + loc];
		i++;
	}
	free(aux->content);
	aux->content = new_str;
}
