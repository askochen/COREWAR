/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 01:26:56 by ederbano          #+#    #+#             */
/*   Updated: 2017/10/28 01:27:00 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int	ft_grow_sleep(int sleep)
{
	int m;

	m = 1000000;
	if (sleep < 0)
		sleep = 1;
	if (sleep == 1)
		return (500000);
	if (m / (m / sleep + 1) < 3745)
		return (3745);
	return (m / (m / sleep + 1));
}

int	ft_low_sleep(int sleep)
{
	int m;

	m = 1000000;
	if (sleep < 1)
		sleep = 2;
	if (sleep == m)
		return (m);
	if (sleep - 1 < 1)
		return (m);
	return (m / (m / sleep - 1));
}

int	ft_key_start(t_draw *draw, int sleep)
{
	int ch;

	wattron(draw->win[0], COLOR_PAIR(5));
	ch = 0;
	while (ch != ' ')
	{
		ch = wgetch(draw->win[0]);
		mvwprintw(draw->win[1], 3, 5, "PAUSE");
		wrefresh(draw->win[1]);
		if (ch == KEY_DOWN)
			sleep = ft_low_sleep(sleep);
		if (ch == KEY_UP && sleep != 0)
			sleep = ft_grow_sleep(sleep);
		if (ch == ' ')
			mvwprintw(draw->win[1], 3, 5, "START");
		mvwprintw(draw->win[1], 5, 27, "%d         ", 1000000 / sleep);
		if (ch == 'q' || ch == 'Q')
		{
			ft_destr_wins(draw);
			exit(0);
		}
		wrefresh(draw->win[1]);
	}
	return (sleep);
}

int	ft_case_key(int key, t_draw *draw, int sleep)
{
	if (key == KEY_DOWN)
		sleep = ft_low_sleep(sleep);
	if (key == KEY_UP && sleep != 0)
		sleep = ft_grow_sleep(sleep);
	if (key == KEY_LEFT)
		sleep = 1000000;
	if (key == KEY_RIGHT)
		sleep = 1;
	if (key == ' ')
		mvwprintw(draw->win[1], 3, 5, "START");
	mvwprintw(draw->win[1], 5, 27, "%d	      ", 1000000 / sleep);
	if (key == 'q' || key == 'Q')
	{
		ft_destr_wins(draw);
		exit(0);
	}
	return (sleep);
}

int	ft_key_processing(t_draw *draw, int sleep)
{
	int ch;
	int rep_ch;

	wattron(draw->win[0], COLOR_PAIR(5));
	ch = wgetch(draw->win[0]);
	rep_ch = 0;
	while (ch == ' ' && rep_ch != ' ')
	{
		mvwprintw(draw->win[1], 3, 5, "PAUSE");
		wrefresh(draw->win[1]);
		rep_ch = wgetch(draw->win[0]);
		sleep = ft_case_key(rep_ch, draw, sleep);
	}
	sleep = ft_case_key(ch, draw, sleep);
	mvwprintw(draw->win[1], 5, 27, "%d	", 1000000 / sleep);
	wrefresh(draw->win[1]);
	return (sleep);
}
