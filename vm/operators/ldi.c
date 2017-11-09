/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:59:16 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:59:17 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void			ldi_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	unsigned int	first;
	unsigned int	second;
	int				sum;

	first = ft_check_first(ms, pr, arg, 0);
	if (arg->type_param[1] == T_DIR)
		second = arg->param[1];
	else
		second = pr->reg[arg->param[1] - 1];
	sum = first + second;
	sum = get_pc(pr->pc + sum % IDX_MOD);
	pr->reg[arg->param[2] - 1] = ft_uint(sum, (char *)ms->memory);
	if (pr->reg[arg->param[2] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
