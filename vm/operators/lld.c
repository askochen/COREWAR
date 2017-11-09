/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:59:45 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:59:46 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void	lld_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int		ind;

	if (arg->type_param[0] == T_DIR)
		pr->reg[arg->param[1] - 1] = arg->param[0];
	else
	{
		ind = (arg->param[0] + pr->pc) % MEM_SIZE;
		pr->reg[arg->param[1] - 1] = ft_uint(ind, (char *)ms->memory);
	}
	if (pr->reg[arg->param[1] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
