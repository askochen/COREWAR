/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:42:00 by ederbano          #+#    #+#             */
/*   Updated: 2017/10/28 01:42:07 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	init_colors(void)
{
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(50, COLOR_BLACK, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_GREEN);
	init_pair(20, COLOR_WHITE, COLOR_BLUE);
	init_pair(30, COLOR_WHITE, COLOR_RED);
	init_pair(40, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
}

void	ft_fill_gen_win(t_mstruc *inst, t_draw *draw)
{
	int x;
	int y;
	int k;
	int col;

	k = 0;
	y = 1;
	while (++y < 66)
	{
		x = 2;
		while (x < 194)
		{
			col = ft_get_st_pair(inst, draw, k);
			inst->col_map[k] = col;
			wattron(draw->win[0], COLOR_PAIR(col));
			mvwprintw(inst->gen_win, y, x, "%.2x", inst->memory[k++]);
			wattroff(draw->win[0], COLOR_PAIR(col));
			x += 3;
		}
	}
	wrefresh(inst->gen_win);
}

void	show_players(t_mstruc *inst, t_draw *draw)
{
	int			h;
	int			w;
	int			i;
	t_players	*tmp;

	h = 12;
	w = 5;
	i = 0;
	tmp = inst->players;
	wmove(draw->win[1], h, w);
	while (i < inst->num_of_players)
	{
		wprintw(draw->win[1], "Player -%d :", tmp->pl_num);
		wattron(draw->win[1], COLOR_PAIR(i + 1));
		wprintw(draw->win[1], " %s", tmp->header->prog_name);
		wattroff(draw->win[1], COLOR_PAIR(i + 1));
		wmove(draw->win[1], ++h, w);
		wprintw(draw->win[1], "	Last live :			");
		wmove(draw->win[1], ++h, w);
		wprintw(draw->win[1], "	Lives in current period :");
		h += 2;
		wmove(draw->win[1], h, w);
		tmp = tmp->next;
		i++;
	}
}

void	create_labels(t_draw *draw)
{
	int	h;
	int	w;

	getyx(draw->win[1], h, w);
	h += 5;
	w += 5;
	wattron(draw->win[1], COLOR_PAIR(5));
	mvwprintw(draw->win[1], 3, 5, "START");
	mvwprintw(draw->win[1], h, w, "Cycles/second limit:");
	mvwprintw(draw->win[1], h + 3, w, "CYCLE: 0");
	mvwprintw(draw->win[1], h + 5, w, "Processes: 0");
	h = 30;
	mvwprintw(draw->win[1], h, w, "Live for current period :");
	mvwprintw(draw->win[1], h + 8, w, "CYCLE_TO_DIE :");
	mvwprintw(draw->win[1], h + 10, w, "CYCLE_DELTA :     %d", CYCLE_DELTA);
	mvwprintw(draw->win[1], h + 12, w, "NBR_LIVE :	       %d", NBR_LIVE);
	mvwprintw(draw->win[1], h + 14, w, "MAX_CHECKS :      %d", MAX_CHECKS);
}

t_draw	*init_wind(void)
{
	t_draw *draw;

	initscr();
	draw = (t_draw *)malloc(sizeof(t_draw));
	start_color();
	init_colors();
	noecho();
	curs_set(0);
	draw->win[0] = newwin(68, 195, 0, 0);
	draw->win[1] = newwin(68, 70, 0, 196);
	nodelay(draw->win[0], TRUE);
	keypad(draw->win[0], TRUE);
	wattron(draw->win[0], COLOR_PAIR(6));
	wborder(draw->win[0], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattron(draw->win[1], COLOR_PAIR(6));
	wborder(draw->win[1], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(draw->win[0]);
	wrefresh(draw->win[1]);
	create_labels(draw);
	return (draw);
}
