/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:58:25 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:58:30 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void		and_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	pr->reg[arg->param[2] - 1] = ft_check_param(ms, pr, arg, 0) &
	ft_check_param(ms, pr, arg, 1);
	if (pr->reg[arg->param[2] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}

int			ft_check_param(t_mstruc *ms, t_process *pr, t_opcode *arg, int idx)
{
	int		ind;

	if (arg->type_param[idx] == T_DIR)
		return (arg->param[idx]);
	else if (arg->type_param[idx] == T_IND)
	{
		ind = ((arg->param[idx] % IDX_MOD) + pr->pc) % MEM_SIZE;
		return (ft_uint(ind, (char *)ms->memory));
	}
	else
		return (pr->reg[arg->param[idx] - 1]);
}
