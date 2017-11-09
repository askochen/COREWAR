/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:49:42 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/16 18:49:44 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_die_part(t_process *lst, t_mstruc *inst, int *live_flag, t_draw *dr)
{
	t_players		*tmp;

	tmp = inst->players;
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

void	ft_cycle_to_vis(t_process *lst, t_mstruc *inst, int *l_flag, t_draw *dr)
{
	*l_flag += 1;
	inst->ind += inst->cycle_to_die;
	if (inst->live_current_per >= NBR_LIVE || *l_flag == MAX_CHECKS)
	{
		*l_flag = 0;
		if (inst->cycle_to_die > CYCLE_DELTA)
			inst->cycle_to_die -= CYCLE_DELTA;
		else
		{
			inst->cycle_to_die = 0;
			inst->total_process = 0;
			ft_vis_winner(inst, dr);
		}
	}
	inst->live_current_per = 0;
	ft_die_part(lst, inst, l_flag, dr);
}

int		ft_begin_vis(t_mstruc *inst, t_draw *draw)
{
	int		sleep;

	sleep = 10000;
	inst->gen_win = draw->win[0];
	ft_fill_gen_win(inst, draw);
	show_players(inst, draw);
	output_core(inst, draw);
	sleep = ft_key_start(draw, sleep);
	return (sleep);
}

void	ft_core_war_viz(t_mstruc *inst, int live_flag)
{
	t_process		*lst;
	t_draw			*draw;
	int				sleep;

	draw = init_wind();
	sleep = ft_begin_vis(inst, draw);
	while (++(inst->total_cycle) >= 0)
	{
		output_core(inst, draw);
		lst = inst->process;
		if (lst == NULL)
			ft_vis_winner(inst, draw);
		while (lst)
		{
			ft_validate_opcode(lst, inst, 0);
			wrefresh(draw->win[0]);
			sleep = ft_key_processing(draw, sleep);
			lst = lst->next;
		}
		if (((inst->total_cycle - inst->ind) % inst->cycle_to_die) == 0)
			ft_cycle_to_vis(inst->process, inst, &live_flag, draw);
		usleep(sleep);
	}
}

void	ft_choose_one(t_mstruc *inst)
{
	int		live_flag;

	init_operators();
	ft_create_process(inst);
	ft_fill_opcode_mem(inst);
	inst->total_process = inst->num_of_players;
	live_flag = 0;
	if (inst->bonus_flag)
		ft_core_war_viz(inst, live_flag);
	else
		ft_core_war(inst, live_flag);
}
