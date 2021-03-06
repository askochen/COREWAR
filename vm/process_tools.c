/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:16:31 by askochen          #+#    #+#             */
/*   Updated: 2017/10/28 01:16:36 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int			get_pc(int pc)
{
	int		i;

	i = pc;
	while (i < 0)
	{
		i = i + MEM_SIZE;
	}
	return (i % MEM_SIZE);
}

t_process	*copy_process(t_process *rhs)
{
	t_process		*pr;
	int				i;

	i = 0;
	pr = ft_init_process();
	pr->number = rhs->number;
	pr->pc = rhs->pc;
	pr->carry = rhs->carry;
	pr->live_flag = rhs->live_flag;
	pr->prev = NULL;
	pr->next = NULL;
	while (i < REG_NUMBER)
	{
		pr->reg[i] = rhs->reg[i];
		++i;
	}
	return (pr);
}

void		new_process(t_process *rpr, t_mstruc *ms, int pc)
{
	t_process		*pr;

	pr = copy_process(rpr);
	pr->pc = pc;
	pr->next = ms->process;
	ms->process->prev = pr;
	ms->process = pr;
}

t_process	*delete_process(t_process *pr, t_mstruc *ms)
{
	t_process		*proc;

	ft_kill_corr(ms, pr->pc);
	proc = pr->next;
	if (pr == ms->process)
		ms->process = ms->process->next;
	if (pr->next != NULL)
		pr->next->prev = pr->prev;
	if (pr->prev != NULL)
		pr->prev->next = pr->next;
	ms->total_process -= 1;
	if (pr->opcode)
		free(pr->opcode);
	free(pr);
	return (proc);
}

void		value_to_memory(t_mstruc *ms, int pos, int val)
{
	ms->memory[pos] = (unsigned char)(val >> 24);
	ms->memory[get_pc(pos + 1)] = (unsigned char)(val >> 16);
	ms->memory[get_pc(pos + 2)] = (unsigned char)(val >> 8);
	ms->memory[get_pc(pos + 3)] = (unsigned char)(val);
}
