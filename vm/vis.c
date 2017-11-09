/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:44:15 by ederbano          #+#    #+#             */
/*   Updated: 2017/10/28 01:44:17 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "corewar_vm.h"

int		sum_for_stat(t_mstruc *inst, t_draw *draw)
{
	t_players	*tmp;
	int			sum;

	tmp = inst->players;
	sum = 0;
	while (tmp)
	{
		sum += tmp->live_flag;
		tmp = tmp->next;
	}
	tmp = inst->players;
	return (sum);
}

void	show_stat(t_mstruc *inst, t_draw *draw)
{
	int			new_live;
	int			i;
	t_players	*tmp;
	int			sum;

	i = -1;
	sum = sum_for_stat(inst, draw);
	wmove(draw->win[1], 32, 6);
	tmp = inst->players;
	while (++i < inst->num_of_players)
	{
		mvwprintw(draw->win[1], 33 + i, 5,
		"		                                                ");
		if (sum > 0)
		{
			new_live = ((int)((tmp->live_flag * 100) / sum)) / 2;
			mvwprintw(draw->win[1], 33 + i, 5, "-%d", tmp->pl_num);
			wmove(draw->win[1], 33 + i, 8);
			wattron(draw->win[1], COLOR_PAIR((i + 1) * 10));
			while (new_live--)
				wprintw(draw->win[1], " ");
			wattroff(draw->win[1], COLOR_PAIR((i + 1) * 10));
			tmp = tmp->next;
		}
	}
}

void	output_core(t_mstruc *inst, t_draw *draw)
{
	t_players	*tmp;
	int			h;

	h = 13;
	tmp = inst->players;
	mvwprintw(draw->win[1], 8, 12, "%d	            ", inst->total_cycle);
	mvwprintw(draw->win[1], 10, 16, "%d	            ", inst->total_process);
	mvwprintw(draw->win[1], 38, 23, "%d	             ", inst->cycle_to_die);
	while (tmp)
	{
		mvwprintw(draw->win[1], h++, 38, "%d             ", tmp->last_live);
		mvwprintw(draw->win[1], h, 38, "%d             ", tmp->live_flag);
		h += 3;
		tmp = tmp->next;
	}
	show_stat(inst, draw);
	wrefresh(draw->win[1]);
}

void	ft_vis_winner(t_mstruc *inst, t_draw *draw)
{
	t_players *lst;
	t_players *winner;

	lst = inst->players;
	winner = lst;
	while (lst)
	{
		if (winner->last_live <= lst->last_live)
			winner = lst;
		lst = lst->next;
	}
	wattron(draw->win[1], COLOR_PAIR(7));
	mvwprintw(draw->win[1], 48, 8, "WE HAVE THE WINNER");
	mvwprintw(draw->win[1], 50, 8,
	"Congratulations to player #%d ", winner->pl_num);
	mvwprintw(draw->win[1], 52, 8,
	"His name is :\"%s\"", winner->header->prog_name);
	output_core(inst, draw);
	wrefresh(draw->win[1]);
	wattroff(draw->win[1], COLOR_PAIR(7));
	while (wgetch(draw->win[1]) != 'q' && wgetch(draw->win[1]) != 'Q')
		;
	ft_destr_wins(draw);
	ft_del_struct(inst);
	exit(0);
}

void	ft_destr_wins(t_draw *draw)
{
	delwin(draw->win[0]);
	delwin(draw->win[1]);
	endwin();
}
