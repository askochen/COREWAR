/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:10:21 by askochen          #+#    #+#             */
/*   Updated: 2017/10/27 18:51:30 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*check_file_name(char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if (len < 3)
		ft_error("Bad file_name\n", -1);
	if (*(str + len - 2) != '.')
		ft_error("Bad file_name\n", -1);
	if (*(str + len - 1) != 's')
		ft_error("Bad file_name\n", -1);
	if (*(str + len - 3) == '/')
		ft_error("Bad file_name\n", -1);
	return (ft_strdup(str));
}

t_to_compile	*pars_file(t_new_list *list, t_to_compile *main_struct)
{
	int		counter;

	counter = 1;
	while (main_struct->name == NULL || main_struct->comment == NULL)
	{
		list = ignore_empty_lines(list, &counter);
		if (list == NULL)
			ft_error("No code\n", -1);
		if (ft_strstr(list->line, ".name") != NULL)
			list = pars_name(list, main_struct, &counter);
		else if (ft_strstr(list->line, ".comment") != NULL)
			list = pars_comment(list, main_struct, &counter);
		else
			ft_error("Syntax error in comment ", counter);
	}
	pars_code(list, main_struct, &counter);
	if (main_struct->code == NULL)
		ft_error("Bad code", counter);
	return (main_struct);
}

t_new_list		*pars_name(t_new_list *list, t_to_compile *main_struct, int *i)
{
	t_new_list	*temp;
	char		*str;

	temp = list;
	if (main_struct->name != NULL)
		ft_error("Syntax error: double .name", *i);
	if (temp == NULL)
		ft_error("Syntax error: No name!", *i);
	str = ignore_white_space(list->line);
	if (ft_strncmp(str, ".name", 5) != 0)
		ft_error("Syntax error: .name ", *i);
	str = str + 5;
	str = ignore_white_space(str);
	if (*str != '"')
		ft_error("Syntax error: No name!", *i);
	list = ft_get_string(list, str + 1, &(main_struct->name), i);
	if (ft_strlen(main_struct->name) > PROG_NAME_LENGTH)
		ft_error("Champion name too long (Max length 128)", *i);
	return (list);
}

t_new_list		*pars_comment(t_new_list *l, t_to_compile *main_struct, int *i)
{
	t_new_list		*temp;
	char			*str;

	temp = l;
	if (main_struct->comment != NULL)
		ft_error("Syntax error: double .comment", *i);
	if (temp == NULL)
		ft_error("Syntax error: No comment", *i);
	str = ignore_white_space(l->line);
	if (ft_strncmp(str, ".comment", 8) != 0)
		ft_error("Syntax error: in .comment", *i);
	str = str + 8;
	str = ignore_white_space(str);
	if (*str != '"')
		ft_error("Syntax error: No comment", *i);
	l = ft_get_string(l, str + 1, &(main_struct->comment), i);
	if (ft_strlen(main_struct->name) > COMMENT_LENGTH)
		ft_error("Champion comment too long (Max length 2048)", *i);
	return (l);
}

t_new_list		*ft_get_string(t_new_list *list, char *s, char **m_s, int *i)
{
	char		*temp;
	char		*str;

	while ((temp = ft_strchr(s, '"')) == NULL)
	{
		*m_s = ft_merge(*m_s, s);
		list = list->next;
		if (list == NULL)
			ft_error("Syntax error: String without end", *i);
		s = list->line;
		*i = *i + 1;
	}
	if (is_empty_line(temp + 1) == 0)
		ft_error("Syntax error ", *i);
	str = ft_strnew(temp - s);
	str = ft_strncpy(str, s, temp - s);
	*m_s = ft_merge(*m_s, str);
	free(str);
	*i = *i + 1;
	return (list->next);
}
