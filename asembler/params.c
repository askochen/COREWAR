/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:08:39 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 19:08:42 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_realloc(char *ptr, int size, char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	if (ptr == NULL)
		i = 0;
	else
		i = (int)ft_strlen(ptr);
	if (!(tmp = (char *)malloc(sizeof(char) * (i + size + 1))))
		return (NULL);
	i = 0;
	while (ptr != NULL && ptr[i])
	{
		tmp[i] = ptr[i];
		i++;
	}
	j = -1;
	while (++j < size)
		tmp[i++] = buf[j];
	tmp[i] = '\0';
	if (ptr != NULL)
		free(ptr);
	return (tmp);
}

void	ft_reg(t_code *inst, int num)
{
	int		i;
	char	*str;

	inst->par_size[num] = 1;
	if (num == 0 && inst->coding_byte_flag)
		inst->coding_byte += 64;
	else if (num == 1 && inst->coding_byte_flag)
		inst->coding_byte += 16;
	else if (num == 2 && inst->coding_byte_flag)
		inst->coding_byte += 4;
	i = 1;
	str = NULL;
	while (inst->params[num][i] != ',' && inst->params[num][i] != '\0')
	{
		str = ft_realloc(str, 1, &inst->params[num][i]);
		i++;
	}
	inst->par[num] = (unsigned int)ft_atoi(str);
	free(str);
}

void	ft_dir(t_code *inst, int num)
{
	int		i;
	char	*str;

	inst->par_size[num] = inst->dir_size;
	if (num == 0 && inst->coding_byte_flag)
		inst->coding_byte += 128;
	else if (num == 1 && inst->coding_byte_flag)
		inst->coding_byte += 32;
	else if (num == 2 && inst->coding_byte_flag)
		inst->coding_byte += 8;
	i = 0;
	str = NULL;
	if (inst->params[num][1] != ':')
	{
		while (inst->params[num][++i] != ',' && inst->params[num][i] != '\0')
			str = ft_realloc(str, 1, &inst->params[num][i]);
		if (inst->dir_size == 4)
			inst->par[num] = (unsigned int)ft_atoi(str);
		else
			inst->par[num] = (unsigned short)ft_atoi(str);
		free(str);
	}
	else
		ft_cut_label(num, inst, 1);
}

void	ft_ind(t_code *inst, int num)
{
	int		i;
	char	*str;

	inst->par_size[num] = 2;
	if (num == 0 && inst->coding_byte_flag)
		inst->coding_byte += 192;
	else if (num == 1 && inst->coding_byte_flag)
		inst->coding_byte += 48;
	else if (num == 2 && inst->coding_byte_flag)
		inst->coding_byte += 12;
	i = -1;
	str = NULL;
	if (inst->params[num][0] != ':')
	{
		while (inst->params[num][++i] != ',' && inst->params[num][i] != '\0')
			str = ft_realloc(str, 1, &inst->params[num][i]);
		inst->par[num] = (unsigned short)ft_atoi(str);
		free(str);
	}
	else
		ft_cut_label(num, inst, 2);
}

void	ft_convert_param(t_code *inst)
{
	int num;

	num = inst->num_param;
	while (num)
	{
		if (inst->params[inst->num_param - num][0] == 'r')
			ft_reg(inst, inst->num_param - num);
		else if (inst->params[inst->num_param - num][0] == '%')
			ft_dir(inst, inst->num_param - num);
		else
			ft_ind(inst, inst->num_param - num);
		num--;
	}
	num = inst->num_param;
	while (num--)
		inst->row_size += inst->par_size[num];
	if (inst->coding_byte)
		inst->row_size += 1;
	inst->row_size += 1;
}
