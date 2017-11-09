/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_part_changes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:37:18 by ederbano          #+#    #+#             */
/*   Updated: 2017/10/28 01:37:20 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void		ft_print_carrs(t_mstruc *inst)
{
	int			x;
	int			y;
	t_process	*pr;

	pr = inst->process;
	while (pr != NULL)
	{
		wattron(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pr->pc)] * 10));
		x = ((get_pc(pr->pc)) % 64) * 3 + 2;
		y = (get_pc(pr->pc)) / 64 + 2;
		mvwprintw(inst->gen_win, y, x, "%.2x", inst->memory[get_pc(pr->pc)]);
		wattroff(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pr->pc)] * 10));
		pr = pr->next;
	}
	wrefresh(inst->gen_win);
}

void		ft_kill_corr(t_mstruc *inst, int pos)
{
	int x;
	int y;

	wattron(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pos)]));
	x = (get_pc(pos)) % 64 * 3 + 2;
	y = (get_pc(pos)) / 64 + 2;
	mvwprintw(inst->gen_win, y, x, "%.2x", inst->memory[get_pc(pos)]);
	wattroff(inst->gen_win, COLOR_PAIR(inst->col_map[get_pc(pos)]));
	wrefresh(inst->gen_win);
}
