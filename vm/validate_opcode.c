/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_opcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:11:22 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/27 19:11:29 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_create_process(t_mstruc *inst)
{
	t_process	*process_lst;
	t_players	*players_lst;
	int			pos;

	process_lst = ft_init_process();
	players_lst = inst->players;
	pos = 0;
	while (players_lst)
	{
		process_lst->reg[0] = players_lst->pl_num * -1;
		process_lst->number = players_lst->pl_num;
		process_lst->pc = pos;
		if (players_lst->next)
		{
			process_lst->prev = ft_init_process();
			process_lst->prev->next = process_lst;
			process_lst = process_lst->prev;
		}
		players_lst = players_lst->next;
		pos += MEM_SIZE / inst->num_of_players;
	}
	inst->process = process_lst;
}

void	ft_validate_comand(t_process *process, t_mstruc *inst)
{
	int		pc;

	process->opcode = ft_init_opcode();
	pc = process->pc % MEM_SIZE;
	process->opcode->operation = inst->memory[pc];
	process->operation = process->opcode->operation;
	process->opcode->row_size += 1;
	if (process->opcode->operation < 1 || process->opcode->operation > 16)
	{
		ft_print_corr(inst, process->pc, (process->pc + 1) % MEM_SIZE);
		process->pc = (process->pc + 1) % MEM_SIZE;
		process->validation_flag = 0;
		process->op_cycle = -1;
		if (process->opcode)
			free(process->opcode);
		process->opcode = NULL;
	}
	else
		process->op_cycle = g_op_tab[process->opcode->operation - 1].cycles - 1;
}

void	ft_validate_opcode(t_process *process, t_mstruc *inst, int flag)
{
	if (process->op_cycle == -1)
		ft_validate_comand(process, inst);
	else if (process->op_cycle > 1)
		process->op_cycle--;
	else
	{
		if (ft_opcode(process->pc + 1, inst, process) == 0)
			ft_comands(inst, process, process->opcode);
		else
		{
			ft_print_corr(inst, process->pc,
						(process->pc + process->opcode->row_size) % MEM_SIZE);
			process->pc = (process->pc + process->opcode->row_size) % MEM_SIZE;
		}
		process->validation_flag = 0;
		process->op_cycle = -1;
		if (process->opcode)
			free(process->opcode);
		process->opcode = NULL;
	}
}
