/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:10:00 by askochen          #+#    #+#             */
/*   Updated: 2017/10/27 20:23:31 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		add_str_to_list(t_new_list **list, char *str)
{
	t_new_list	*temp;

	temp = (t_new_list*)malloc(sizeof(t_new_list*));
	if (temp == NULL)
		return ;
	temp->next = NULL;
	temp->line = ft_strdup(str);
	ft_lstadd_back(list, temp);
}

void		ft_del_list(t_new_list *list)
{
	t_new_list	*temp;

	while (list != NULL)
	{
		temp = list->next;
		free(list->line);
		free(list);
		list = temp;
	}
}

void		ft_lstadd_back(t_new_list **alst, t_new_list *new)
{
	t_new_list	*temp;

	temp = *alst;
	if (alst != NULL && new != NULL)
	{
		if (*alst == NULL)
		{
			*alst = new;
			return ;
		}
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

t_new_list	*read_file_to_list(int fd)
{
	char			*str;
	t_new_list		*list;

	list = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		add_str_to_list(&list, str);
		free(str);
	}
	close(fd);
	return (list);
}
