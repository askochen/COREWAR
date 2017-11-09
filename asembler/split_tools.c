/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:09:43 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:09:47 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			char_num(char *str, char ch)
{
	int i;

	i = 0;
	while (*str != '\0')
	{
		if (*str == ch)
			++i;
		++str;
	}
	return (i);
}

char		**param_split(char *s, char c)
{
	int		num;
	int		i;
	char	**res;
	char	*temp;

	if (s == NULL)
		return (NULL);
	i = 0;
	num = char_num(s, c);
	res = (char **)malloc(sizeof(char *) * (num + 2));
	while (i <= num)
	{
		temp = ft_strchr(s, c);
		if (temp != NULL)
		{
			res[i] = ft_strsub(s, 0, temp - s);
			s = temp + 1;
		}
		else
			res[i] = ft_strdup(s);
		i++;
	}
	res[num + 1] = NULL;
	return (res);
}

int			word_counter(char *str)
{
	int		in_word;
	int		count;

	in_word = 0;
	count = 0;
	while (*str != '\0')
	{
		if ((*str != ' ' && *str != '\t') && in_word == 0)
		{
			++count;
			in_word = 1;
		}
		if (*str == ' ' || *str == '\t')
			in_word = 0;
		++str;
	}
	return (count);
}
