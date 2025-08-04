/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:47:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/08/04 14:00:19 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_include_nnode(t_list **lst, char *str);
char	*ft_fillnl(t_list **lst, int size_nl);
int		ft_verify_nlend(t_list **lst);
int		ft_fillstock(int fd, t_list **head);

char	*get_next_line(int fd)
{
	static t_list	*stock = NULL;
	char			*rtn;
	int				size_nl;

	size_nl = 0;
	rtn = NULL;
	if (fd < 0)
	{
		ft_cleanls(&stock, 1);
		stock = NULL;
		return (NULL);
	}
	while (size_nl == 0)
	{
		if (ft_fillstock(fd, &stock))
			return (ft_cleanls(&stock, 1));
		size_nl = ft_verify_nlend(&stock);
	}
	rtn = ft_fillnl(&stock, size_nl);
	if (!rtn)
		return (ft_cleanls(&stock, 1));
	if (stock && ((char *)stock->content)[0] == 0)
		ft_cleanls(&stock, 1);
	return (rtn);
}

int	ft_fillstock(int fd, t_list **head)
{
	int		size_read;
	char	*b_read;
	char	*b_read_rs;

	b_read = malloc(BUFFER_SIZE + 1);
	if (!b_read)
		return (1);
	size_read = read(fd, b_read, BUFFER_SIZE);
	if ((size_read < 0) || (size_read == 0 && !*head))
		free(b_read);
	if ((size_read < 0) || (size_read == 0 && !*head))
		return (1);
	b_read[size_read] = 0;
	b_read_rs = (char *)malloc(size_read + 1);
	if (!b_read_rs)
		return (1);
	b_read_rs[size_read] = 0;
	while (*b_read != '\0')
		*(b_read_rs++) = *(b_read++);
	free(b_read - size_read);
	if (ft_include_nnode(head, b_read_rs - size_read))
		return (1);
	return (0);
}

int	ft_include_nnode(t_list **lst, char *str)
{
	t_list	*aux;
	t_list	*tail;

	aux = malloc(sizeof(t_list));
	if (!aux)
		return (1);
	aux->content = str;
	aux->next = NULL;
	if (*lst)
	{
		tail = *lst;
		while (tail->next)
			tail = tail->next;
		if (((char *)tail->content)[0] == str[0] && str[0] == 0)
		{
			free(str);
			free(aux);
			return (0);
		}
		tail->next = aux;
		return (0);
	}
	*lst = aux;
	return (0);
}

char	*ft_fillnl(t_list **lst, int size_nl)
{
	t_list	*aux;
	int		i;
	int		i_rtn;
	char	*rtn;

	i_rtn = 0;
	rtn = (malloc(size_nl + 1));
	if (!rtn)
		return (NULL);
	while (i_rtn < size_nl)
	{
		i = 0;
		aux = *lst;
		while (i_rtn < size_nl && (((char *)aux->content)[i] != 0
			|| ((char *)aux->content)[0] == 0))
			rtn[i_rtn++] = ((char *)aux->content)[i++];
		if (((char *)aux->content)[i] == 0 && i > 0)
			*lst = aux->next;
		if (((char *)aux->content)[i] == 0 && i > 0)
			ft_cleanls(&aux, 0);
		else
			ft_lst_content_substr(&*lst, i);
	}
	rtn[i_rtn] = 0;
	return (rtn);
}

int	ft_verify_nlend(t_list **lst)
{
	t_list	*tail;
	t_list	*aux;
	int		i;
	int		count;

	count = 0;
	tail = *lst;
	while (tail)
	{
		i = 0;
		while (((char *)tail->content)[i] != 0)
		{
			if (((char *)tail->content)[i] == '\n')
				return (count + 1);
			i++;
			count++;
		}
		aux = tail;
		tail = tail->next;
	}
	if (((char *)aux->content)[0] == 0)
		return (count);
	return (0);
}
