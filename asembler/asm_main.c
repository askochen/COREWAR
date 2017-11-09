/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:02:31 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 19:02:35 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_del_to_compile(t_to_compile *elem)
{
	t_new_list *tmp;

	free(elem->file_name);
	free(elem->name);
	free(elem->comment);
	while (elem->code)
	{
		free(elem->code->line);
		tmp = elem->code;
		elem->code = elem->code->next;
		free(tmp);
	}
	free(elem);
}

void	ft_del_code(t_code *inst)
{
	int		i;
	t_code	*tmp;

	while (inst)
	{
		if (inst->label)
			free(inst->label);
		i = inst->num_param;
		while (i > 0)
			free(inst->params[--i]);
		free(inst->params);
		tmp = inst;
		inst = inst->next;
		free(tmp);
	}
}

char	*ft_fname(int size, char *fname)
{
	char	*str;
	char	*ex;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * (size + 3));
	i = -1;
	ex = COR;
	while (++i < size - 1)
		str[i] = fname[i];
	j = 0;
	while (i < size + 3)
		str[i++] = ex[j++];
	return (str);
}

t_code	*ft_encoding(t_to_compile *elem, t_headers *strc)
{
	int			i;
	t_code		*inst;
	t_code		*copy_inst;
	t_new_list	*copy_code;

	inst = ft_t_code_new();
	copy_inst = inst;
	copy_code = elem->code;
	i = -1;
	while (copy_code)
	{
		ft_f_str_param(inst, copy_code, ++i, 0);
		if (copy_code->next)
		{
			inst->next = ft_t_code_new();
			inst = inst->next;
		}
		else
			inst->next = NULL;
		copy_code = copy_code->next;
	}
	ft_label(copy_inst);
	strc->prog_size = ft_prog_size(copy_inst);
	return (copy_inst);
}

void	asm_main(t_to_compile *elem)
{
	int			i;
	int			fd;
	char		*str;
	t_code		*inst;
	t_headers	s;

	str = ft_fname((int)ft_strlen(elem->file_name), elem->file_name);
	if ((fd = open(str, O_CREAT | O_TRUNC | O_RDWR, S_IREAD | S_IWRITE)) < 0)
		ft_error("Can't open file\n", -1);
	free(str);
	s.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(s.prog_name, PROG_NAME_LENGTH + 1);
	i = -1;
	while (elem->name[++i])
		s.prog_name[i] = elem->name[i];
	ft_bzero(s.comment, COMMENT_LENGTH + 1);
	i = -1;
	while (elem->comment[++i])
		s.comment[i] = elem->comment[i];
	inst = ft_encoding(elem, &s);
	ft_write_to_cor(s, inst, fd);
	close(fd);
	ft_del_to_compile(elem);
	ft_del_code(inst);
}
