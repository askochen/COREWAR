/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_argc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:42:42 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/11 21:42:43 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

char	*ft_num_player(int *ind, char **params, t_mstruc *inst, int i)
{
	long int	num;
	char		*str;

	if (params[*ind + 1] && params[*ind + 2])
	{
		*ind += 1;
		str = ft_num_player_val(ind, params, inst);
		if (str)
			return (str);
		else
		{
			i = ft_lst_len(inst->players, 1, 0);
			if (i < MAX_PLAYERS)
			{
				num = ft_atoi_mod(params[*ind]);
				inst->player_num[i] = num;
				*ind += 1;
				return (ft_create_new_player(*ind, params, inst));
			}
			else
				return (MANY_CHAMP);
		}
	}
	return (NUM_WRONG);
}

int		ft_file_extension(char *str)
{
	char	*ptr;
	int		i;

	i = 0;
	if ((ptr = ft_strstr(str, ".cor")) == NULL)
		return (1);
	while (*ptr)
	{
		i++;
		ptr++;
	}
	if (i != 4)
		return (1);
	return (0);
}

char	*ft_create_new_player(int i, char **params, t_mstruc *inst)
{
	t_players	*tmp;
	int			fd;
	char		*str;

	inst->num_of_players += 1;
	tmp = inst->players;
	if (tmp)
	{
		tmp = (t_players *)ft_lst_end(tmp, 1);
		tmp->next = ft_init_players();
		tmp = tmp->next;
	}
	else
	{
		inst->players = ft_init_players();
		tmp = inst->players;
	}
	if (ft_file_extension(params[i]))
		return (EXTENSION);
	if ((fd = open(params[i], O_RDONLY)) < 0)
		return (CANT_READ);
	str = ft_validation_cor(fd, tmp);
	close(fd);
	return (str);
}

void	ft_validation_arg(char **params, t_mstruc *inst, int i)
{
	char		*fail;

	while (params[++i])
	{
		if (ft_strcmp(params[i], BONUS) == 0 || ft_strcmp(params[i], AFF) == 0)
			fail = ft_check_bonus(inst, params[i]);
		else if (ft_strcmp(params[i], DUMP) == 0)
			fail = ft_dump_num(&i, params, inst);
		else if (ft_strcmp(params[i], NUM) == 0)
			fail = ft_num_player(&i, params, inst, -1);
		else
			fail = ft_create_new_player(i, params, inst);
		if (fail)
			ft_error_vm(fail, inst, params, i);
	}
	if ((i = ft_lst_len(inst->players, 1, 0)) == 0)
		ft_error_vm(NOT_CHAMP, inst, params, -1);
	if (i > MAX_PLAYERS)
		ft_error_vm(MANY_CHAMP, inst, params, -1);
	ft_give_num(inst->players, 0, -1, inst);
	if ((fail = ft_check_repeat_num(inst)) != NULL)
		ft_error_vm(fail, inst, params, -1);
	inst->players = ft_sort_players(inst->players);
	ft_dell_mas(params);
}
