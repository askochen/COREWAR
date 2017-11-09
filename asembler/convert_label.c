/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:09:53 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 19:09:55 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_length(t_code *inst, int start, int end)
{
	t_code	*copy;
	int		len;

	copy = inst;
	len = 0;
	while (copy)
	{
		if (copy->row >= start && copy->row < end)
			len += copy->row_size;
		copy = copy->next;
	}
	return (len);
}

void			ft_count_len(t_code *inst, int num_r, t_code *ptr)
{
	int start;
	int end;
	int len;
	int flag;

	flag = 0;
	if (ptr->row > num_r)
	{
		start = num_r;
		end = ptr->row;
		flag = 1;
	}
	else
	{
		end = num_r;
		start = ptr->row;
	}
	len = ft_length(inst, start, end);
	if (flag)
		ptr->par[ptr->ptr_label] = USHRT_MAX - len + 1;
	else
		ptr->par[ptr->ptr_label] = len;
}

void			ft_label(t_code *inst)
{
	t_code *ptr;
	t_code *copy;

	ptr = inst;
	while (ptr)
	{
		if (ptr->ptr_label >= 0)
		{
			copy = inst;
			while (copy)
			{
				if (copy->label_flag &&
					!ft_strcmp(ptr->params[ptr->ptr_label], copy->label))
				{
					ft_count_len(inst, copy->row, ptr);
					break ;
				}
				copy = copy->next;
			}
		}
		ptr = ptr->next;
	}
}

void			ft_cut_label(int num, t_code *inst, int flag)
{
	char	*str;
	int		size;

	if (flag == 1)
	{
		size = (int)ft_strlen(inst->params[num]) - 2;
		str = ft_realloc(NULL, size, &inst->params[num][2]);
	}
	else
	{
		size = (int)ft_strlen(inst->params[num]) - 1;
		str = ft_realloc(NULL, size, &inst->params[num][1]);
	}
	inst->ptr_label = num;
	free(inst->params[num]);
	inst->params[num] = str;
}

unsigned int	ft_prog_size(t_code *inst)
{
	t_code			*copy;
	unsigned int	size;

	size = 0;
	copy = inst;
	while (copy)
	{
		size += copy->row_size;
		copy = copy->next;
	}
	return (size);
}
