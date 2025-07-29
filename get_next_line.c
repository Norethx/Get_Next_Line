/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:47:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/07/29 20:45:43 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(t_list **lst);
void	verify_line(char *str, t_list **stock, size_t bff_lido);
void	ls_lnclean(t_list **head);
int		verify_newline(t_list *head);

char	*get_next_line(int fd)
{
	static t_list	*b_read = 0;
	void			*str;
	char			*rtn = NULL;
	size_t			size_r;
	int				flag;

	flag = 0;
	if (b_read)
		rtn = fill_line(&b_read);
	while (rtn == NULL)
	{
		str = malloc(BUFFER_SIZE);
		if (!str)
			return (NULL);
		size_r = (int)read(fd, str, BUFFER_SIZE);
		if ((int)size_r <= 0 || size_r > BUFFER_SIZE)
		{
			if (flag == 0)
			{
				free(str);
				return (NULL);
			}
			if (flag > 0)
			{
				verify_line("", &b_read, 1);
				rtn = fill_line(&b_read);
				free(str);
				break;
			}
		}
		verify_line(str, &b_read, size_r);
		free(str);
		rtn = fill_line(&b_read);
		flag++;
	}
	ls_lnclean(&b_read);
	// if (flag > 0)
	// {
	// 	free(b_read->content);
	// 	free(b_read);
	// }
	return (rtn);
}

void	ls_lnclean(t_list **head)
{
	t_list	*aux  = 0;;
	t_list	*aux_head  = 0;;

	aux_head = *head;
	while (aux_head)
	{
		aux = aux_head;
		aux_head = aux_head->next;
		if (((char *)aux->content)[0] == '\0'
			|| ((char *)aux->content)[0] == '\n')
		{
			free(aux->content);
			free(aux);
			break ;
		}
		free(aux->content);
		free(aux);
	}
	*head = aux_head;
}

void	verify_line(char *str, t_list **stock, size_t bff_lido)
{
	char	*c  = 0;;
	int		i  = 0;;
	t_list	*new  = 0;;
	t_list	*tail  = 0;;

	i = 0;
	tail = *stock;
	while (tail && tail->next)
		tail = tail->next;
	while (i++ < (int)bff_lido)
	{
		c = malloc(1);
		new = malloc(sizeof(t_list));
		c[0] = ((char *)str)[i - 1];
		new->content = (void *)c;
		new->next = NULL;
		if (*stock == NULL)
			*stock = new;
		else
			tail->next = new;
		tail = new;
		new = new->next;
	}
}

char	*fill_line(t_list **lst)
{
	t_list	*head = 0;;
	size_t	loc = 0;;
	size_t	i = 0;;
	char	*rtn = 0;;

	i = 0;
	rtn = NULL;
	if (!*lst)
		return (rtn);
	loc = verify_newline(*lst);
	if (loc != 0)
	{
		head = *lst;
		rtn = malloc(loc + 1);
		while (i < loc)
		{
			rtn[i] = ((char *)head->content)[0];
			head = head->next;
			i++;
		}
		rtn[i] = 0;
	}
	return (rtn);
}

int	verify_newline(t_list *head)
{
	t_list	*tail = 0;;
	int		loc = 0;;

	tail = head;
	loc = 0;
	while (tail->next && ((char *)tail->content)[0] != '\n'
		&& ((char *)tail->content)[0] != 0)
	{
		tail = tail->next;
		loc++;
	}
	if (((char *)tail->content)[0] != '\n' && ((char *)tail->content)[0] != 0)
		return (0);
	return (loc + 1);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*teste;

// 	fd = open("41_no_nl", 0);
// 	teste = get_next_line(fd);
// 	printf("%s", teste);
// 	free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// 	// teste = get_next_line(fd);
// 	// printf("%s", teste);
// 	// free(teste);
// }
