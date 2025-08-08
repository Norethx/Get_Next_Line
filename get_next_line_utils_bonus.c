/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:03:22 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:38 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	ft_lst_content_substr(t_list **lst, int loc, char *sec)
{
	int		i;
	char	*new_str;
	t_list	*aux;

	i = loc;
	aux = *lst;
	while (((char *)aux->content)[i] != 0)
		i++;
	new_str = malloc((i - loc + 1));
	if (!new_str)
	{
		free(sec);
		return (1);
	}
	new_str[i - loc] = 0;
	i = 0;
	while (((char *)aux->content)[i + loc] != 0)
	{
		new_str[i] = ((char *)aux->content)[i + loc];
		i++;
	}
	free(aux->content);
	aux->content = new_str;
	return (0);
}
