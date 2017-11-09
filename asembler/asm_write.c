/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 18:36:07 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/03 18:36:08 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_write_param(int i, t_code *copy, int fd)
{
	while (++i < copy->num_param)
	{
		if (copy->par_size[i] == 4)
		{
			copy->par[i] = ((copy->par[i] >> 24) & 0xff) |
							((copy->par[i] << 8) & 0xff0000) |
							((copy->par[i] >> 8) & 0xff00) |
							((copy->par[i] << 24) & 0xff000000);
		}
		else if (copy->par_size[i] == 2)
		{
			copy->par[i] = ((copy->par[i] >> 8) & 0xff) |
							((copy->par[i] << 8) & 0xff00);
		}
		write(fd, (char *)&copy->par[i], (unsigned int)copy->par_size[i]);
	}
}

void	ft_write_opcode(t_code *inst, int fd)
{
	t_code	*copy;

	copy = inst;
	while (copy)
	{
		if (copy->operation != -1)
		{
			write(fd, (char *)&copy->operation, 1);
			if (copy->coding_byte)
				write(fd, (char *)&copy->coding_byte, 1);
			ft_write_param(-1, copy, fd);
		}
		copy = copy->next;
	}
}

void	ft_write_to_cor(t_headers s, t_code *inst, int fd)
{
	char *str;

	str = ft_strnew(3);
	s.magic = ((s.magic >> 24) & 0xff) | ((s.magic << 8) & 0xff0000) |
				((s.magic >> 8) & 0xff00) | ((s.magic << 24) & 0xff000000);
	write(fd, (char *)&s.magic, 4);
	write(fd, s.prog_name, PROG_NAME_LENGTH + 1);
	write(fd, str, 3);
	s.prog_size = ((s.prog_size >> 24) & 0xff) |
					((s.prog_size << 8) & 0xff0000) |
					((s.prog_size >> 8) & 0xff00) |
					((s.prog_size << 24) & 0xff000000);
	write(fd, (char *)&s.prog_size, 4);
	write(fd, s.comment, COMMENT_LENGTH + 1);
	write(fd, str, 3);
	ft_write_opcode(inst, fd);
	free(str);
}
