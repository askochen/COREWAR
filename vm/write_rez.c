/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_rez.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 14:33:23 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/20 14:33:24 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_write_contestants(int i, char *str, t_players *pl)
{
	write(1, "Introducing contestants...", 26);
	write(1, "\n", 1);
	while (pl)
	{
		write(1, "* Player ", 9);
		str = ft_itoa(pl->pl_num);
		write(1, str, ft_strlen(str));
		free(str);
		write(1, ", weighing ", 11);
		str = ft_itoa(pl->header->prog_size);
		free(str);
		write(1, str, ft_strlen(str));
		write(1, " bytes, \"", 9);
		write(1, pl->header->prog_name,
		ft_strlen(pl->header->prog_name));
		write(1, "\" (\"", 4);
		write(1, pl->header->comment,
		ft_strlen(pl->header->comment));
		write(1, "\") !", 4);
		write(1, "\n", 1);
		pl = pl->next;
	}
}

void	ft_write_winner(t_players *player)
{
	char *str;

	write(1, "Contestant ", 11);
	str = ft_itoa(player->pl_num);
	write(1, str, ft_strlen(str));
	free(str);
	write(1, ", \"", 3);
	write(1, player->header->prog_name, ft_strlen(player->header->prog_name));
	write(1, "\", has won !\n", 13);
}
