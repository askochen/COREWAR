/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:14:01 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:14:11 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			add_left_label(t_label_list **ll, char *str, int *i)
{
	t_label_list	*temp;

	if (*ll == NULL)
	{
		*ll = new_label(str, *i, 1, 0);
		return ;
	}
	temp = *ll;
	while (temp->next != NULL)
	{
		if (ft_strcmp(temp->name, str) == 0)
		{
			temp->is_left = 1;
			return ;
		}
		temp = temp->next;
	}
	if (ft_strcmp(temp->name, str) == 0)
		temp->is_left = 1;
	else
		temp->next = new_label(str, *i, 1, 0);
}

void			add_right_label(t_label_list **ll, char *str, int *i)
{
	t_label_list	*temp;

	if (*ll == NULL)
	{
		*ll = new_label(str, *i, 0, 1);
		return ;
	}
	temp = *ll;
	while (temp->next != NULL)
	{
		if (ft_strcmp(temp->name, str) == 0)
		{
			temp->is_right = 1;
			return ;
		}
		temp = temp->next;
	}
	if (ft_strcmp(temp->name, str) == 0)
		temp->is_right = 1;
	else
		temp->next = new_label(str, *i, 0, 1);
}

t_label_list	*new_label(char *str, int i, char is_left, char is_right)
{
	t_label_list	*new;

	new = (t_label_list*)malloc(sizeof(t_label_list));
	new->name = ft_strdup(str);
	new->is_left = is_left;
	new->is_right = is_right;
	new->row = i;
	new->next = NULL;
	return (new);
}

void			check_label(t_label_list **ll)
{
	t_label_list	*temp;

	temp = *ll;
	while (temp != NULL)
	{
		if ((temp->is_right == 1) && (temp->is_left == 0))
			ft_error(ft_strjoin("Wrong label ", temp->name), temp->row);
		temp = temp->next;
	}
}

void			remove_label_list(t_label_list **ll)
{
	t_label_list *temp;
	t_label_list *temp_b;

	temp = *ll;
	while (temp != NULL)
	{
		free(temp->name);
		temp_b = temp->next;
		free(temp);
		temp = temp_b;
	}
}
