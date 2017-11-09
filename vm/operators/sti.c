/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:59:24 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:59:26 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void	sti_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int		first;
	int		second;
	int		sum;

	first = ft_check_first(ms, pr, arg, 1);
	if (arg->type_param[2] == T_DIR)
		second = arg->param[2];
	else
		second = pr->reg[arg->param[2] - 1];
	sum = (first + second) % IDX_MOD;
	sum = get_pc(pr->pc + sum);
	value_to_memory(ms, sum, pr->reg[arg->param[0] - 1]);
	ft_print_in_gen(sum, ms, pr);
	ft_print_corr(ms, pr->pc, pr->pc + pr->opcode->row_size);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}

int		ft_check_first(t_mstruc *ms, t_process *pr, t_opcode *arg, int idx)
{
	int		ind;

	if (arg->type_param[idx] == T_DIR)
		return (arg->param[idx]);
	else if (arg->type_param[idx] == T_REG)
		return (pr->reg[arg->param[idx] - 1]);
	else
	{
		ind = get_pc(pr->pc + arg->param[idx]);
		return (ft_uint(ind, (char *)ms->memory));
	}
}
