/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 20:17:28 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 20:17:29 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_usage(void)
{
	ft_putstr("Usage: ./corewar [-dump N | -v] | [-v | -a] | [-dump N & -a] | "
					"[[-n & -a] or [-n & -v] or [-n & -dump N]]\n");
	ft_putstr("\n");
	ft_putstr("#### OUTPUT MODE ########################################\n");
	ft_putstr(" -a      : Prints output from \"aff\"\n");
	ft_putstr(" -v      : Ncurses output mode\n");
	ft_putstr(" -dump N : Dumps memory after N cycles then exits\n");
	ft_putstr(" -n      : Sets the number of the next player\n");
}

void	ft_error_vm(char *error_mes, t_mstruc *inst, char **params, int i)
{
	write(1, "\033[0;33m)", 7);
	write(2, "ERROR : ", 8);
	if (!ft_strcmp(error_mes, MANY_CHAMP) || !ft_strcmp(error_mes, NOT_CHAMP))
		write(2, error_mes, ft_strlen(error_mes));
	else if (!ft_strcmp(error_mes, NUM_WRONG) ||
			!ft_strcmp(error_mes, EXTENSION) ||
			!ft_strcmp(error_mes, NUM_WRONG))
	{
		write(2, error_mes, ft_strlen(error_mes));
		write(2, "  ", 2);
		write(2, params[i], ft_strlen(params[i]));
	}
	else
	{
		write(2, params[i], ft_strlen(params[i]));
		write(2, "  ", 2);
		write(2, error_mes, ft_strlen(error_mes));
	}
	write(1, "\033[0m\n", 5);
	if (params)
		ft_dell_mas(params);
	if (inst)
		ft_del_struct(inst);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_mstruc	*inst;
	char		**params;
	int			i;

	if (argc < 2)
	{
		ft_usage();
		return (0);
	}
	params = (char **)malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (--argc > 0)
	{
		params[i] = ft_realloc(NULL, ft_strlen(argv[i + 1]), argv[i + 1]);
		i++;
	}
	params[i] = NULL;
	inst = ft_init_mstruct();
	ft_validation_arg(params, inst, -1);
	ft_choose_one(inst);
	return (0);
}
