/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 15:28:02 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/21 15:28:03 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_fill_opcode_mem(t_mstruc *inst)
{
	int			j;
	int			ind;
	int			pos;
	t_players	*lst;

	pos = 0;
	lst = inst->players;
	while (lst)
	{
		ind = pos;
		j = -1;
		while (++j < lst->header->prog_size)
		{
			inst->memory[ind] = lst->opcode[j];
			ind++;
		}
		pos += MEM_SIZE / inst->num_of_players;
		lst = lst->next;
	}
}

void	ft_winner(t_mstruc *inst)
{
	t_players		*lst;
	t_players		*winner;

	lst = inst->players;
	winner = lst;
	while (lst)
	{
		if (winner->last_live <= lst->last_live)
			winner = lst;
		lst = lst->next;
	}
	if (inst->bonus_flag == 0)
		ft_write_winner(winner);
	ft_del_struct(inst);
	exit(0);
}

void	ft_die_part_cl(t_process *lst, t_mstruc *inst, int *live_flag)
{
	t_players		*tmp;

	tmp = inst->players;
	inst->live_current_per = 0;
	while (tmp)
	{
		tmp->live_flag = 0;
		tmp = tmp->next;
	}
	while (lst)
	{
		if (lst->live_flag == 0)
			lst = delete_process(lst, inst);
		else
		{
			lst->live_flag = 0;
			lst = lst->next;
		}
	}
}

void	ft_cycle_to_die(t_process *lst, t_mstruc *inst, int *live_flag)
{
	*live_flag += 1;
	inst->ind += inst->cycle_to_die;
	if (inst->live_current_per >= NBR_LIVE || *live_flag == MAX_CHECKS)
	{
		*live_flag = 0;
		if (inst->cycle_to_die > CYCLE_DELTA)
			inst->cycle_to_die -= CYCLE_DELTA;
		else
		{
			inst->cycle_to_die = 0;
			ft_winner(inst);
		}
	}
	ft_die_part_cl(lst, inst, live_flag);
}

void	ft_core_war(t_mstruc *inst, int live_flag)
{
	t_process		*lst;

	ft_write_contestants(-1, NULL, inst->players);
	while (++(inst->total_cycle) != inst->dump_flag)
	{
		lst = inst->process;
		if (lst == NULL)
			ft_winner(inst);
		while (lst)
		{
			ft_validate_opcode(lst, inst, 0);
			lst = lst->next;
		}
		if (((inst->total_cycle - inst->ind) % inst->cycle_to_die) == 0)
			ft_cycle_to_die(inst->process, inst, &live_flag);
	}
	output_dump(inst);
	ft_del_struct(inst);
}
