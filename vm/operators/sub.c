/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:57:48 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:57:53 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void	sub_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	pr->reg[arg->param[2] - 1] = pr->reg[arg->param[0] - 1] -
	pr->reg[arg->param[1] - 1];
	if (pr->reg[arg->param[2] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
