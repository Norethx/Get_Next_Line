/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:47:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/07/28 20:26:59 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(t_list **lst);
void	verify_line(char *str, t_list **stock, size_t bff_lido);

char	*get_next_line(int fd)
{
	static int		save_fd = -1;
	static t_list	*b_read;
	void			*str;
	t_list			*head;
	t_list			*aux;
	char			*rtn;

	str = NULL;
	if (!b_read)
		rtn =  NULL;
	else
		rtn = fill_line(&b_read);
	if (save_fd == -1)
		save_fd = fd;
	while (rtn == NULL)
	{
		str = malloc(BUFFER_SIZE);
		int teste = (int)read(save_fd, str, BUFFER_SIZE);
		if (teste <= 0)
		{
			free(str);
			return (NULL);
		}
		verify_line(str, &b_read,teste);
		free(str);
		rtn = fill_line(&b_read);
	}
	head = b_read;
	while (b_read && ((char *)b_read->content)[0] != '\0' && ((char *)b_read->content)[0] != '\n')
		b_read = b_read->next;
	if (b_read && ((char *)b_read->content)[0] == '\0')
		while (b_read->next != NULL)
			b_read = b_read->next;
	else
		b_read = b_read->next;
	while(head != b_read)
	{
		aux = head;
		head = head->next;
		free(aux->content);
		free(aux);
	}
	return (rtn);
}

void	verify_line(char *str, t_list **stock, size_t bff_lido)
{
	char	*c;
	int		i;
	t_list	*list_content;
	t_list	*tail;

	tail = *stock;
	list_content = NULL;
	if (tail)
	{
		while (tail->next)
			tail = tail->next;
	}
	i = 0;
	while (i < (int)bff_lido)
	{
		if (*stock == NULL)
		{
			c = malloc(1);
			list_content = malloc(sizeof(t_list));
			list_content->content = NULL;
			c[0] = ((char *)str)[i];
			list_content->content = (void *)c;
			list_content->next = NULL;
			*stock = list_content;
			tail = list_content;
		}
		else
		{
			c = malloc(1);
			if (!list_content)
				list_content = tail;
			c[0] = ((char *)str)[i];
			tail = malloc(sizeof(t_list));
			tail->content = (void *)c;
			tail->next = NULL;
			list_content->next = tail;
			list_content = tail;
			tail = tail->next;
		}
		i++;
	}
}

char	*fill_line(t_list **lst)
{
	t_list	*head;
	size_t	loc;
	size_t	i;
	char	*rtn;
	t_list	*tail = *lst;

	loc = 0;
	i = 0;
	head = *lst;
	while (head->next && ((char *)head->content)[0] != '\n' && ((char *)head->content)[0] != 0)
	{
		head = head->next;
		loc++;
	}
	if (((char *)head->content)[0] != '\n' && ((char *)head->content)[0] != 0)
		return (NULL);
	else
	{
		rtn = malloc(loc + 2);
		rtn[loc+1] = 0;
		while (i <= loc)
		{
			rtn[i] = ((char *)tail->content)[0];
			tail = tail->next;
			i++;
		}
	}
	return (rtn);
}

int	main(void)
{
	int fd;
	char *teste;

	fd = open("teste.txt",0);
	teste = get_next_line(0);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	teste = get_next_line(fd);
	printf("%s",teste);
	free(teste);
	// teste = get_next_line(fd);
	// printf("%s",teste);
	// free(teste);
}
