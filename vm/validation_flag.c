/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:31:00 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/27 18:31:01 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

long int	ft_atoi_mod(char *str)
{
	long int	res;
	int			minus;

	res = 0;
	minus = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
		*str == '\r' || *str == '\v' || *str == '\f')
		++str;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		++str;
	}
	return (res * minus);
}

char		*ft_dump_validation(int *ind, char **params, t_mstruc *inst, int i)
{
	int flag;

	flag = 0;
	if (params[*ind + 1])
	{
		while (params[*ind + 1][++i])
		{
			if (ft_isdigit(params[*ind + 1][i]) == 0)
			{
				if (i == 0 && params[*ind + 1][i] == '-')
					;
				else
					flag++;
			}
		}
		if (ft_strlen(params[*ind + 1]) > 10 ||
			((inst->dump_flag = ft_atoi_mod(params[*ind + 1])) >= INT_MAX ||
			inst->dump_flag <= INT_MIN))
			flag++;
		if (flag)
			return (NUM_WRONG);
		*ind += 1;
		return (NULL);
	}
	return (NUM_WRONG);
}

char		*ft_dump_num(int *ind, char **params, t_mstruc *inst)
{
	if (inst->dump_flag == -14570)
		return (ft_dump_validation(ind, params, inst, -1));
	return (MULTIPLE_USE);
}

char		*ft_num_player_val(int *ind, char **params, t_mstruc *inst)
{
	long int	num;
	int			i;

	i = -1;
	while (params[*ind][++i])
	{
		if (ft_isdigit(params[*ind][i]) == 0)
		{
			*ind -= 1;
			return (NUM_WRONG);
		}
	}
	num = ft_atoi_mod(params[*ind]);
	if (num < 1 || num > MAX_ARGS_NUMBER)
	{
		*ind -= 1;
		return (NUM_WRONG);
	}
	else
		return (NULL);
}

char		*ft_check_bonus(t_mstruc *inst, char *str)
{
	if (!ft_strcmp(str, BONUS))
	{
		if (inst->bonus_flag)
			return (MULTIPLE_USE);
		else
		{
			inst->bonus_flag += 1;
			return (NULL);
		}
	}
	else
	{
		if (inst->bonus_aff)
			return (MULTIPLE_USE);
		else
		{
			inst->bonus_aff += 1;
			return (NULL);
		}
	}
}
