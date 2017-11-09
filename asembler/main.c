/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:13:41 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:13:47 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_error(char *str, int i)
{
	char	*new;

	ft_putstr(str);
	if (i >= 0)
	{
		ft_putstr(" in line: ");
		new = ft_itoa(i);
		ft_putstr(new);
		ft_putstr("!\n");
		free(new);
	}
	exit(1);
}

t_to_compile	*init_main_struct(void)
{
	t_to_compile	*temp;

	temp = (t_to_compile*)malloc(sizeof(t_to_compile));
	temp->name = NULL;
	temp->comment = NULL;
	temp->code = NULL;
	temp->file_name = NULL;
	return (temp);
}

int				main(int argc, char **argv)
{
	t_new_list		*list;
	int				fd;
	t_to_compile	*m_s;

	if (argc != 2)
		ft_error("Bad number of argument!\n", -1);
	m_s = init_main_struct();
	m_s->file_name = check_file_name(argv[1]);
	if ((fd = open(argv[1], O_RDONLY, 0)) == -1)
		ft_error("Can't open file!\n", -1);
	list = read_file_to_list(fd);
	m_s = pars_file(list, m_s);
	asm_main(m_s);
	ft_putstr("Writing output program!");
	ft_putstr("\n");
	return (0);
}
