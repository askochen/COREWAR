/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_argc_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 17:50:04 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/16 17:50:06 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		ft_give_num_help(t_mstruc *inst)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (++i <= MAX_PLAYERS)
	{
		j = -1;
		flag = 0;
		while (++j < MAX_PLAYERS)
		{
			if (inst->player_num[j] == i)
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 0)
			break ;
	}
	return (i);
}

void	ft_give_num(t_players *ptr, int i, int j, t_mstruc *inst)
{
	while (ptr)
	{
		if (inst->player_num[i])
			ptr->pl_num = inst->player_num[i];
		else
		{
			ptr->pl_num = ft_give_num_help(inst);
			inst->player_num[i] = ptr->pl_num;
		}
		++i;
		ptr = ptr->next;
	}
}

char	*ft_check_repeat_num(t_mstruc *inst)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (inst->player_num[i] != 0)
		{
			j = -1;
			while (++j < MAX_PLAYERS)
			{
				if (j != i && inst->player_num[j] != 0)
					if (inst->player_num[i] == inst->player_num[j])
						return (BAD_NUM_OF_PL);
			}
		}
	}
	return (NULL);
}
