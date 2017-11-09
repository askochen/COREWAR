/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:59:06 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:59:08 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void	zjmp_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	if (pr->carry == 1)
	{
		ft_print_corr(ms, pr->pc, get_pc(pr->pc + (arg->param[0] % IDX_MOD)));
		pr->pc = get_pc(pr->pc + (arg->param[0] % IDX_MOD));
	}
	else
	{
		ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
		pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
	}
}
