/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 14:54:00 by askochen          #+#    #+#             */
/*   Updated: 2017/10/27 20:24:55 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "op.h"
# define COR			"cor"

typedef struct			s_new_list
{
	char				*line;
	struct s_new_list	*next;
}						t_new_list;

typedef struct			s_to_compile
{
	char				*file_name;
	char				*name;
	char				*comment;
	t_new_list			*code;
}						t_to_compile;

typedef struct			s_label_list
{
	char				*name;
	char				is_left;
	char				is_right;
	unsigned int		row;
	struct s_label_list	*next;
}						t_label_list;

typedef struct			s_op
{
	char				*comand_name;
	int					num_arguments;
	char				arguments_types[3];
	int					opcode;
	int					cycles;
	char				*description;
	char				arguments_byte;
	char				index_size;
}						t_op;

typedef	struct			s_code
{
	int					row;
	int					row_size;
	int					label_flag;
	char				*label;
	int					operation;
	int					coding_byte_flag;
	int					coding_byte;
	int					dir_size;
	int					ptr_label;
	int					num_param;
	unsigned int		par[3];
	int					par_size[3];
	char				**params;
	struct s_code		*next;

}						t_code;

typedef struct			s_helper
{
	int					comands[16];
	int					label_size[16];
	int					coding_byte[16];
	int					var_arg[16][3];
	int					arg_size[16][3];
}						t_helper;

t_op					g_op_tab[17];
t_helper				g_help;

/*
**main.c
*/
void					ft_error(char *str, int i);
t_to_compile			*init_main_struct(void);

/*
**read_file.c.c
*/
t_new_list				*read_file_to_list(int fd);
void					ft_lstadd_back(t_new_list **alst, t_new_list *new);
void					ft_del_list(t_new_list *list);
void					print_list(t_new_list **list);
void					add_str_to_list(t_new_list **list, char *str);
void					print_list_label(t_label_list **list);

/*
**tools.c.c
*/
char					*ft_merge(char *str1, char *str2);
int						is_label_char(char ch);
int						is_empty_line(char *str);
t_new_list				*ignore_empty_lines(t_new_list *list, int *counter);
char					*ignore_white_space(char *str);

/*
**pars_line.c
*/
t_to_compile			*pars_file(t_new_list *list, t_to_compile *main_s);
t_new_list				*pars_name(t_new_list *list, t_to_compile *m_s, int *i);
t_new_list				*pars_comment(t_new_list *l, t_to_compile *m_s, int *i);
t_new_list				*ft_get_string(t_new_list *l, char *s,
						char **m_s, int *i);
char					*check_file_name(char *str);

/*
**pars_code.c
*/
void					pars_code(t_new_list *temp, t_to_compile *m_s, int *i);
void					check_line(char *str, t_to_compile *m_s, int *i,
						t_label_list **ll);
char					*get_label(char *str, int *i);
int						get_comand(char *str, int *it);
void					check_params(char *s, int in, int *it,
						t_label_list **ll);

/*
**label_tools.c
*/
void					add_left_label(t_label_list **ll, char *s, int *i);
t_label_list			*new_label(char *s, int i, char is_left, char is_right);
void					add_right_label(t_label_list **ll, char *str, int *i);
void					check_label(t_label_list **ll);
void					remove_label_list(t_label_list **ll);

/*
**param_tools.c
*/
int						get_param_len(char *str);
char					*get_new_param(char *str);
int						get_param_num(char **param);
void					check_cur_param(char **s, int in, int *i,
						t_label_list **ll);
char					*remove_whitespace(char *str, int len);
/*
**check_param.c
*/
int						is_reg(char *str);
int						is_dir(char *str, t_label_list **ll, int *it);
int						is_indir(char *str, t_label_list **ll, int *it);
int						is_number(char *str);
int						is_right_label(char *str);

/*
***code_tools.c
*/
t_new_list				*add_code_line(t_to_compile *m_s);
char					*ft_merge_lines(char *str1, char *str2, char *str3);
char					*get_final_param(char *str);
void					remove_parameters(char **split);

/*
**split_tools.c
*/
int						char_num(char *str, char ch);
char					**param_split(char *s, char c);
int						word_counter(char *str);

/*
**asm.h
*/
void					asm_main(t_to_compile *elem);
char					*ft_fname(int size, char *fname);
t_code					*ft_encoding(t_to_compile *elem, t_headers *strc);
t_code					*ft_t_code_new(void);
void					ft_f_str_param(t_code *in, t_new_list *c, int i, int j);
char					*ft_realloc(char *ptr, int size, char *buf);
int						ft_num_operation(char *code_line, int *j, t_code *inst);
void					ft_fill_op_param(int size, char *code_l, t_code *inst);
void					ft_split_param(t_code *inst, char *str);
void					ft_convert_param(t_code *inst);
void					ft_reg(t_code *inst, int num);
void					ft_dir(t_code *inst, int num);
void					ft_ind(t_code *inst, int num);
void					ft_label(t_code *inst);
void					ft_count_len(t_code *inst, int num_r, t_code *ptr);
int						ft_length(t_code *inst, int start, int end);
unsigned int			ft_prog_size(t_code *inst);
void					ft_write_to_cor(t_headers s, t_code *inst, int fd);
void					ft_write_opcode(t_code *inst, int fd);
void					ft_write_param(int i, t_code *copy, int fd);
void					ft_del_to_compile(t_to_compile *elem);
void					ft_del_code(t_code *inst);
void					ft_cut_label(int num, t_code *inst, int flag);

#endif
