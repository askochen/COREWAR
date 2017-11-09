/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:10:46 by askochen          #+#    #+#             */
/*   Updated: 2017/10/10 20:10:51 by askochen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		pars_code(t_new_list *temp, t_to_compile *main_struct, int *i)
{
	t_label_list	*labels;

	labels = NULL;
	while (temp != NULL)
	{
		if (is_empty_line(temp->line) == 0)
		{
			check_line(temp->line, main_struct, i, &labels);
		}
		*i = *i + 1;
		temp = temp->next;
	}
	check_label(&labels);
	remove_label_list(&labels);
}

void		check_line(char *str, t_to_compile *m_s, int *i, t_label_list **ll)
{
	char		*temp;
	int			index;
	t_new_list	*new;

	new = add_code_line(m_s);
	str = ignore_white_space(str);
	temp = get_label(str, i);
	if (temp != NULL)
	{
		add_left_label(ll, temp, i);
		str = str + ft_strlen(temp) + 1;
		str = ignore_white_space(str);
		new->line = ft_merge_lines(new->line, temp, ": ");
		free(temp);
	}
	if (is_empty_line(str) == 1)
		return ;
	index = get_comand(str, i);
	new->line = ft_merge_lines(new->line, g_op_tab[index].comand_name, " ");
	str = str + ft_strlen(g_op_tab[index].comand_name);
	str = ignore_white_space(str);
	check_params(str, index, i, ll);
	temp = get_final_param(str);
	new->line = ft_merge(new->line, temp);
	free(temp);
}

char		*get_label(char *str, int *i)
{
	char	*temp;
	char	*iter;

	iter = str;
	temp = ft_strchr(str, ':');
	if (temp == NULL)
		return (NULL);
	if (iter == temp)
		ft_error("Syntax error: no label  ", *i);
	while (iter != temp)
	{
		if (is_label_char(*iter) == 0)
			return (NULL);
		++iter;
	}
	iter = ft_strnew(temp - str);
	iter = ft_strncpy(iter, str, temp - str);
	return (iter);
}

int			get_comand(char *str, int *it)
{
	int		i;
	int		len;

	i = 15;
	while (i >= 0)
	{
		len = ft_strlen(g_op_tab[i].comand_name);
		if (ft_strncmp(str, g_op_tab[i].comand_name, len) == 0)
		{
			if (ft_isalpha(str[len]) || str[len] == ':' || ft_isdigit(str[len]))
				ft_error("Syntax error in comand's name", *it);
			return (i);
		}
		--i;
	}
	ft_error("Bad operator's name ", *it);
	return (0);
}

void		check_params(char *str, int index, int *it, t_label_list **ll)
{
	char	*new;
	char	**split;
	int		num;

	new = get_new_param(str);
	split = param_split(new, ',');
	if (split == NULL)
		ft_error("Syntax error: No parameters ", *it);
	num = get_param_num(split);
	if (num != g_op_tab[index].num_arguments)
		ft_error("Syntax error: Wrong number of arguments ", *it);
	check_cur_param(split, index, it, ll);
	remove_parameters(split);
	free(split);
	free(new);
}
