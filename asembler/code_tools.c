/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 17:33:32 by askochen          #+#    #+#             */
/*   Updated: 2017/10/15 17:33:37 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_new_list		*add_code_line(t_to_compile *m_s)
{
	t_new_list		*temp;
	t_new_list		*new;

	new = (t_new_list*)malloc(sizeof(t_new_list));
	new->line = ft_strdup("");
	new->next = NULL;
	if (m_s->code == NULL)
		m_s->code = new;
	else
	{
		temp = m_s->code;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

char			*ft_merge_lines(char *str1, char *str2, char *str3)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_merge(str1, str2);
	temp2 = ft_merge(temp1, str3);
	return (temp2);
}

char			*get_final_param(char *str)
{
	char	*temp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	temp = str;
	while (*temp != '\0' && *temp != '#')
	{
		if (*temp != ' ' && *temp != '\t')
			++count;
		++temp;
	}
	temp = ft_strnew(count);
	while (i < count)
	{
		if (*str != ' ' && *str != '\t')
		{
			temp[i] = *str;
			++i;
		}
		++str;
	}
	return (temp);
}

void			remove_parameters(char **split)
{
	while (*split != NULL)
	{
		free(*split);
		++split;
	}
}
