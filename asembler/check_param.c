/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 15:03:00 by askochen          #+#    #+#             */
/*   Updated: 2017/10/08 15:03:05 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_reg(char *str)
{
	int		i;
	char	*temp;

	if (*str != 'r')
		return (0);
	temp = str + 1;
	while (*temp != '\0')
	{
		if (ft_isdigit(*temp) == 0)
			return (0);
		++temp;
	}
	i = ft_atoi(str + 1);
	if (i >= 0 && i <= REG_NUMBER)
		return (1);
	else
		return (0);
}

int		is_dir(char *str, t_label_list **ll, int *it)
{
	if (*str != '%')
		return (0);
	return (is_indir(str + 1, ll, it));
}

int		is_indir(char *str, t_label_list **ll, int *it)
{
	if (is_number(str) == 1)
		return (1);
	if (is_right_label(str) == 1)
	{
		add_right_label(ll, str + 1, it);
		return (1);
	}
	return (0);
}

int		is_number(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '\0')
		return (0);
	if (*str == '-')
		++str;
	while (ft_isdigit(*str) == 1)
		++str;
	if (*str == '\0')
		return (1);
	else
		return (0);
}

int		is_right_label(char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '\0')
		return (0);
	if (*str != ':')
		return (0);
	++str;
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (is_label_char(*str) == 0)
			return (0);
		++str;
	}
	return (1);
}
