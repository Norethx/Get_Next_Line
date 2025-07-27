/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:47:47 by rgomes-d          #+#    #+#             */
/*   Updated: 2025/07/27 20:31:22 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	*get_next_line(int fd)
{
static int save_fd;
static t_list *b_read;
if(save_fd == 0)
{
	save_fd = fd;
	b_read = Verify_line(fd);
}
if(!save_fd)
	save_fd = 1;
}

t_list *Verify_line(int fd)
{
	size_t BUFFER_SIZE = 42;
	void *str;
	t_list *list_content;
	list_content = malloc(sizeof(t_list));
	list_content->content = '\0';
	t_list *head;
	t_list *tail;
	char *c = malloc(1);
	int i = 0;

	read(fd,str,BUFFER_SIZE);
	while(i < BUFFER_SIZE)
	{
		if (list_content->content == NULL)
		{
			c[0] = ((char *)str)[i];
			list_content->content = (void *)c;
			list_content->next = NULL;
			tail = tail;
			head = list_content;
		}
		else
		{
			c = malloc(1);
			c[0] = ((char *)str)[i];
			tail = malloc(sizeof(t_list));
			tail->content = (void *)c;
			tail->next = NULL;
			list_content->next = tail;
			list_content = list_content->next;
		}
		i++;
	}


}

int	main(void)
{
	get_next_line(1);
	get_next_line(1);
	get_next_line(1);
	get_next_line(1);
	get_next_line(1);
	return (0);


	list_content = head;
	while (list_content)
	{
		printf("%c",((char *)list_content->content)[0]);
		list_content = list_content->next;
	}

	while (head)
	{
		list_content = head;
		head = head->next;
		free(list_content->content);
		free(list_content);
	}
}

