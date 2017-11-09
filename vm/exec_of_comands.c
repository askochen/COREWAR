/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_of_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:16:52 by askochen          #+#    #+#             */
/*   Updated: 2017/10/28 01:16:57 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	init_operators(void)
{
	g_operator = (t_op_type*)malloc(sizeof(t_op_type) * 16);
	g_operator[0] = live_com;
	g_operator[1] = ld_com;
	g_operator[2] = st_com;
	g_operator[3] = add_com;
	g_operator[4] = sub_com;
	g_operator[5] = and_com;
	g_operator[6] = or_com;
	g_operator[7] = xor_com;
	g_operator[8] = zjmp_com;
	g_operator[9] = ldi_com;
	g_operator[10] = sti_com;
	g_operator[11] = fork_com;
	g_operator[12] = lld_com;
	g_operator[13] = lldi_com;
	g_operator[14] = lfork_com;
	g_operator[15] = aff_com;
}

void	ft_comands(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	g_operator[pr->operation - 1](ms, pr, arg);
}
