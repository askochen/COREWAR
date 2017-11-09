/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:11:35 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:11:42 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_param_len(char *str)
{
	int		i;

	i = 0;
	while (*str != '\0' && *str != '#')
	{
		if (*str != ' ' && *str != '\t')
			++i;
		++str;
	}
	return (i);
}

char		*remove_whitespace(char *str, int len)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strnew(len);
	while (i < len)
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

char		*get_new_param(char *str)
{
	char	*temp;

	temp = ft_strchr(str, '#');
	if (temp == NULL)
		return (ft_strdup(str));
	else
		return (ft_strsub(str, 0, temp - str));
}

int			get_param_num(char **param)
{
	int		i;

	i = 0;
	while (*param != NULL)
	{
		++param;
		++i;
	}
	return (i);
}

void		check_cur_param(char **split, int index, int *it, t_label_list **ll)
{
	char		temp;
	int			num;
	int			i;
	char		*str;

	i = 0;
	num = get_param_num(split);
	while (i < num)
	{
		if (word_counter(split[i]) != 1)
			ft_error("Syntax error: Bad argument ", *it);
		str = remove_whitespace(split[i], get_param_len(split[i]));
		temp = g_op_tab[index].arguments_types[i];
		if (((temp & 1) == 1) && (is_reg(str) == 1))
			++i;
		else if (((temp & 2) == 2) && (is_dir(str, ll, it) == 1))
			++i;
		else if (((temp & 4) == 4) && (is_indir(str, ll, it) == 1))
			++i;
		else
			ft_error("Syntax error: Bad argument ", *it);
		free(str);
	}
}
