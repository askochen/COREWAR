/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:56:19 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 11:56:25 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void	st_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int		position;

	if (arg->type_param[1] == T_REG)
		pr->reg[arg->param[1] - 1] = pr->reg[arg->param[0] - 1];
	else
	{
		position = get_pc(pr->pc + arg->param[1] % IDX_MOD);
		value_to_memory(ms, position, pr->reg[arg->param[0] - 1]);
		ft_print_in_gen(position, ms, pr);
	}
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
