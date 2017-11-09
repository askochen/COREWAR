/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 19:02:58 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 19:03:02 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_code	*ft_t_code_new(void)
{
	t_code *inst;

	inst = (t_code *)malloc(sizeof(t_code));
	inst->row = -1;
	inst->row_size = 0;
	inst->label_flag = 0;
	inst->label = NULL;
	inst->operation = -1;
	inst->coding_byte_flag = 0;
	inst->coding_byte = 0;
	inst->dir_size = -1;
	inst->ptr_label = -1;
	inst->num_param = -1;
	inst->par[0] = 0;
	inst->par[1] = 0;
	inst->par[2] = 0;
	inst->par_size[0] = -1;
	inst->par_size[1] = -1;
	inst->par_size[2] = -1;
	inst->params = NULL;
	inst->next = NULL;
	return (inst);
}

int		ft_num_operation(char *code_line, int *j, t_code *inst)
{
	int		i;
	char	*str;
	int		size;

	size = 0;
	i = -1;
	while (code_line[++i] != ' ')
	{
		size++;
		*j += 1;
	}
	str = ft_realloc(NULL, size, code_line);
	i = -1;
	while (++i < 16)
	{
		if (!ft_strcmp(str, g_op_tab[i].comand_name))
		{
			free(str);
			inst->coding_byte_flag = g_help.coding_byte[i];
			inst->num_param = g_op_tab[i].num_arguments;
			inst->dir_size = g_help.label_size[i];
			return (i + 1);
		}
	}
	return (0);
}

void	ft_split_param(t_code *inst, char *str)
{
	int num;
	int ln;
	int i;
	int nb;

	num = inst->num_param;
	nb = inst->num_param;
	i = -1;
	while (num)
	{
		ln = 0;
		while (str[++i] != ',' && str[i] != '\0')
			ln++;
		inst->params[nb - num] = ft_realloc(NULL, ln, &str[i - ln]);
		num--;
	}
}

void	ft_fill_op_param(int size, char *code_line, t_code *inst)
{
	char *str;

	str = ft_realloc(NULL, size, code_line);
	inst->params = (char **)malloc(sizeof(char *) * inst->num_param);
	ft_split_param(inst, str);
	ft_convert_param(inst);
	free(str);
}

void	ft_f_str_param(t_code *inst, t_new_list *code, int i, int j)
{
	inst->row = i;
	while (code->line[j] != ' ' && code->line[j] != '\0')
		j++;
	if (code->line[j - 1] == ':')
	{
		inst->label = ft_realloc(NULL, j - 1, code->line);
		inst->label_flag = 1;
		if (code->line[j] == '\0' || code->line[j + 1] == '\0')
			return ;
	}
	if (inst->label)
	{
		while (code->line[j] == ' ')
			j++;
		inst->operation = ft_num_operation(&code->line[j], &j, inst);
	}
	else
	{
		j -= j;
		inst->operation = ft_num_operation(code->line, &j, inst);
	}
	while (code->line[j] == ' ')
		j++;
	ft_fill_op_param(ft_strlen(code->line) - j, &code->line[j], inst);
}
