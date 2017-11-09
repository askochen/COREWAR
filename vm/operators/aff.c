/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:00:13 by askochen          #+#    #+#             */
/*   Updated: 2017/10/24 12:00:14 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar_vm.h"

void		aff_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	char	c;

	c = pr->reg[arg->param[0] - 1] % 256;
	if (ms->bonus_aff)
	{
		write(1, "Aff: ", 5);
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
