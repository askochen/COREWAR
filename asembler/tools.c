/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:09:24 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:09:30 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_merge(char *str1, char *str2)
{
	char	*temp;

	if (str2 == NULL)
		return (str1);
	if (str1 == NULL)
		return (ft_strdup(str2));
	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

int			is_label_char(char ch)
{
	char	*temp;

	temp = ft_strchr(LABEL_CHARS, ch);
	if (temp != NULL)
		return (1);
	else
		return (0);
}

int			is_empty_line(char *str)
{
	while (*str != '\0')
	{
		if (*str == '#')
			return (1);
		if (*str != ' ' && *str != '\t')
			return (0);
		++str;
	}
	return (1);
}

t_new_list	*ignore_empty_lines(t_new_list *list, int *counter)
{
	int			state;
	t_new_list	*temp;

	temp = list;
	state = 1;
	while (state == 1)
	{
		if (temp == NULL)
			return (NULL);
		if (is_empty_line(temp->line) == 1)
		{
			*counter = *counter + 1;
			temp = temp->next;
		}
		else
			state = 0;
	}
	return (temp);
}

char		*ignore_white_space(char *str)
{
	while (*str != '\0' && (*str == ' ' || *str == '\t'))
		++str;
	return (str);
}
