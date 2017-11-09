/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 19:18:41 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/12 19:18:43 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		ft_fill_param(t_opcode *op_lst, t_mstruc *inst, int *ind, t_process *pr)
{
	int		i;

	i = -1;
	while (++i < op_lst->num_param)
	{
		if (op_lst->param_size[i] == 1)
		{
			op_lst->param[i] = inst->memory[*ind];
			*ind = (*ind + 1) % MEM_SIZE;
			if (op_lst->param[i] < 1 || op_lst->param[i] > 16)
				return (1);
		}
		else if (op_lst->param_size[i] == 2)
		{
			op_lst->param[i] = ft_ushort(*ind, (char *)inst->memory);
			*ind = (*ind + 2) % MEM_SIZE;
		}
		else
		{
			op_lst->param[i] = ft_uint(*ind, (char *)inst->memory);
			*ind = (*ind + 4) % MEM_SIZE;
		}
	}
	return (0);
}

void	ft_fill_param_size(t_opcode *op_lst)
{
	int		i;

	i = -1;
	while (++i < op_lst->num_param)
	{
		if (g_help.arg_size[op_lst->operation - 1][i])
			op_lst->param_size[i] = g_help.arg_size[op_lst->operation - 1][i];
		else
			op_lst->param_size[i] = ft_var_param(op_lst, i);
	}
	if (op_lst->cod_byte == 0)
	{
		i = -1;
		while (++i < op_lst->num_param)
			op_lst->row_size += op_lst->param_size[i];
	}
}

int		ft_validate_coding_byte(t_process *process)
{
	int				flag;
	int				i;
	int				rez;
	unsigned char	test_byte;
	t_opcode		*code;

	code = process->opcode;
	flag = 0;
	i = -1;
	test_byte = 0;
	while (++i < process->opcode->num_param)
	{
		rez = ft_type_param(code, i, &test_byte);
		if ((rez & g_op_tab[code->operation - 1].arguments_types[i]) != rez)
			flag++;
		else
			code->type_param[i] = rez;
		code->row_size += ft_var_param(code, i);
	}
	code->row_size += 1;
	if (flag || test_byte == 0)
		return (1);
	return (0);
}

int		ft_opcode(int pc, t_mstruc *inst, t_process *process)
{
	int		i;

	i = g_op_tab[process->opcode->operation - 1].num_arguments;
	process->opcode->num_param = i;
	if (g_help.coding_byte[process->opcode->operation - 1])
	{
		process->opcode->cod_byte = inst->memory[pc];
		pc = (pc + 1) % MEM_SIZE;
		if (ft_validate_coding_byte(process))
			return (1);
	}
	ft_fill_param_size(process->opcode);
	if (ft_fill_param(process->opcode, inst, &pc, process))
		return (1);
	return (0);
}
