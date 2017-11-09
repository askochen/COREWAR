/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_print_changes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:29:09 by ederbano          #+#    #+#             */
/*   Updated: 2017/10/28 01:29:12 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void		ft_print_in_gen(int pos, t_mstruc *inst, t_process *proc)
{
	int			cord[2];
	int			i;
	int			color;
	t_players	*tmp;

	i = 0;
	color = 1;
	tmp = inst->players;
	while (tmp != NULL && proc->number != tmp->pl_num)
	{
		color++;
		tmp = tmp->next;
	}
	wattron(inst->gen_win, COLOR_PAIR(color));
	while (i < 4)
	{
		cord[0] = (get_pc((pos + i)) % 64) * 3 + 2;
		cord[1] = (get_pc(pos + i)) / 64 + 2;
		inst->col_map[get_pc(pos + i)] = color;
		mvwprintw(inst->gen_win, cord[1], cord[0], "%.2x",
						inst->memory[get_pc(pos + i++)]);
	}
	wattroff(inst->gen_win, COLOR_PAIR(color));
}

void		ft_print_corr(t_mstruc *inst, int pre, int now)
{
	int x;
	int y;

	wattron(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pre)]));
	x = ((get_pc(pre)) % 64) * 3 + 2;
	y = (get_pc(pre)) / 64 + 2;
	mvwprintw(inst->gen_win, y, x, "%.2x", inst->memory[get_pc(pre)]);
	wattroff(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pre)]));
	wattron(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(now)] * 10));
	x = (get_pc(now)) % 64 * 3 + 2;
	y = (get_pc(now)) / 64 + 2;
	mvwprintw(inst->gen_win, y, x, "%.2x", inst->memory[get_pc(now)]);
	wattroff(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(now)] * 10));
}

t_process	*ft_last_proc(t_mstruc *inst)
{
	t_process	*proc;

	proc = inst->process;
	while (proc->next != NULL)
		proc = proc->next;
	return (proc);
}

int			ft_count_num(t_players *plr, t_process *proc, int c, int pos)
{
	int	num;

	num = 5;
	while (proc != NULL)
	{
		if (proc->pc == pos)
		{
			num = c * 10;
			break ;
		}
		if (proc->pc < pos && (proc->pc + plr->header->prog_size) > pos)
		{
			num = c;
			break ;
		}
		if ((proc->pc + plr->header->prog_size) > pos)
			num = 5;
		plr = plr->next;
		proc = proc->prev;
		c++;
	}
	return (num);
}

int			ft_get_st_pair(t_mstruc *inst, t_draw *draw, int pos)
{
	t_process	*proc;
	t_players	*plr;
	int			num;
	int			c;

	proc = ft_last_proc(inst);
	plr = inst->players;
	c = 1;
	num = ft_count_num(plr, proc, c, pos);
	wattron(inst->gen_win, COLOR_PAIR(num));
	if (num >= 10)
		return (num / 10);
	return (num);
}
