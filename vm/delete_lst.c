/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:15:53 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/27 18:15:54 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

t_players	*ft_copy_player_s(t_players *lst)
{
	t_players	*new;
	int			i;

	new = ft_init_players();
	i = -1;
	while (++i <= PROG_NAME_LENGTH)
		new->header->prog_name[i] = lst->header->prog_name[i];
	i = -1;
	while (++i <= COMMENT_LENGTH)
		new->header->comment[i] = lst->header->comment[i];
	new->header->prog_size = lst->header->prog_size;
	new->header->magic = lst->header->magic;
	new->opcode = lst->opcode;
	new->pl_num = lst->pl_num;
	return (new);
}

void		ft_dell_mas(char **mas)
{
	int		i;

	i = -1;
	while (mas[++i])
		free(mas[i]);
	free(mas);
}

t_players	*ft_dell_players_lst(t_players *lst)
{
	t_players *ptr;

	if (lst)
	{
		while (lst)
		{
			if (lst->header)
				free(lst->header);
			if (lst->opcode)
				free(lst->opcode);
			ptr = lst;
			lst = lst->next;
			free(ptr);
		}
		return (NULL);
	}
	return (NULL);
}

t_process	*ft_dell_process_lst(t_process *lst)
{
	t_process *ptr;

	if (lst)
	{
		while (lst)
		{
			ptr = lst;
			lst = lst->next;
			if (ptr->opcode)
				free(ptr->opcode);
			free(ptr);
		}
		return (NULL);
	}
	return (NULL);
}

void		ft_del_struct(t_mstruc *inst)
{
	if (inst->players)
		inst->players = ft_dell_players_lst(inst->players);
	if (inst->process)
		inst->process = ft_dell_process_lst(inst->process);
	free(inst);
}
