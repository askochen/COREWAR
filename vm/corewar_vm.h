/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:34:06 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/07 18:34:08 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_COREWAR_VM_H
# define COREWAR_VM_COREWAR_VM_H
# include "libft/libft.h"
# include "op.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <ncurses.h>
# define DUMP			"-dump"
# define NUM			"-n"
# define MANY_CHAMP		"Too many champions"
# define NOT_CHAMP		"Not enough champions"
# define NUM_WRONG		"incorrect use of the flag"
# define BONUS			"-v"
# define AFF			"-a"
# define EXTENSION		"Invalid file extension"
# define SMALL			" is too small to be a champion"
# define HEADER			" has an invalid header"
# define DIFF_SIZE		" has a code size that differ from what its header says"
# define LARGE_CODE		" has too large a code"
# define CANT_READ		"Can't read source file"
# define BAD_NUM_OF_PL	"Bad number of player"
# define MULTIPLE_USE	"Multiple use argument"
# define BIG_NAME		"Big name"
# define BIG_COMMENT	"Big comment"

typedef struct			s_opcode
{
	unsigned int		row_size;
	int					operation;
	int					cod_byte;
	int					num_param;
	int					param[3];
	int					param_size[3];
	int					type_param[3];
}						t_opcode;

typedef struct			s_process
{
	int					number;
	int					validation_flag;
	int					operation;
	int					op_cycle;
	int					reg[REG_NUMBER];
	int					pc;
	int					carry;
	int					live_flag;
	t_opcode			*opcode;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

typedef struct			s_players
{
	t_headers			*header;
	unsigned char		*opcode;
	int					pl_num;
	int					live_flag;
	long int			last_live;
	struct s_players	*prev;
	struct s_players	*next;
}						t_players;

typedef struct			s_mstruc
{
	int					bonus_flag;
	int					bonus_aff;
	long int			dump_flag;
	unsigned char		memory[MEM_SIZE];
	short int			col_map[MEM_SIZE];
	int					num_of_players;
	int					player_num[MAX_PLAYERS];
	t_players			*players;
	t_players			mas_player[MAX_PLAYERS];
	t_process			*process;
	int					winner;
	unsigned int		total_process;
	int					ind;
	int					cycle_to_die;
	long int			total_cycle;
	unsigned int		live_current_per;
	unsigned int		live_last_per;
	WINDOW				*gen_win;
}						t_mstruc;

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

typedef struct			s_helper
{
	int					comands[16];
	int					label_size[16];
	int					coding_byte[16];
	int					var_arg[16][3];
	int					arg_size[16][3];
}						t_helper;

typedef struct			s_draw
{
	WINDOW				*win[3];
}						t_draw;

t_helper				g_help;
t_op					g_op_tab[17];
typedef void			(*t_op_type)(t_mstruc *ms, t_process *pr,
						t_opcode *arg);
t_op_type				*g_operator;
void					ft_error_vm(char *error_mes, t_mstruc *inst,
						char **params, int i);
void					ft_usage(void);
long int				ft_atoi_mod(char *str);
char					*ft_dump_validation(int *ind, char **params,
						t_mstruc *inst, int i);
char					*ft_dump_num(int *ind, char **params, t_mstruc *inst);
char					*ft_num_player_val(int *ind, char **params,
						t_mstruc *inst);
char					*ft_check_bonus(t_mstruc *inst, char *str);
void					ft_dell_mas(char **mas);
t_players				*ft_dell_players_lst(t_players *lst);
t_process				*ft_dell_process_lst(t_process *lst);
void					ft_del_struct(t_mstruc *inst);
t_players				*ft_copy_player_s(t_players *lst);
void					show_stat(t_mstruc *inst, t_draw *draw);
void					output_core(t_mstruc *inst, t_draw *draw);
void					ft_vis_winner(t_mstruc *inst, t_draw *draw);
void					ft_destr_wins(t_draw *draw);
void					ft_print_in_gen(int pos, t_mstruc *inst,
						t_process *proc);
void					ft_print_corr(t_mstruc *inst, int pre, int now);
void					ft_kill_corr(t_mstruc *inst, int pos);
int						ft_get_st_pair(t_mstruc *inst, t_draw *draw, int pos);
t_draw					*init_wind(void);
void					show_players(t_mstruc *inst, t_draw *draw);
void					ft_fill_gen_win(t_mstruc *inst, t_draw *draw);
void					create_labels(t_draw *draw);
void					init_colors();
int						ft_key_processing(t_draw *draw, int sleep);
int						ft_key_start(t_draw *draw, int sleep);
int						ft_grow_sleep(int sleep);
int						ft_low_sleep(int sleep);
void					*ft_lst_end(void *lst, int flag);
int						ft_lst_len(void *lst, int flag, int len);
void					ft_sort_players_2(t_players *new, t_players *lst,
						t_players *copy);
void					ft_sort_players_1(t_players *new, t_players *lst,
						t_players *copy);
t_players				*ft_sort_players(t_players *lst);
t_opcode				*ft_init_opcode(void);
t_process				*ft_init_process(void);
t_headers				*ft_init_header(void);
t_mstruc				*ft_init_mstruct(void);
t_players				*ft_init_players(void);
int						ft_uint(int ind, char *str);
short					ft_ushort(int ind, char *str);
char					*ft_realloc(char *ptr, int size, char *buf);
char					*ft_validation_cor(int fd, t_players *player);
char					*ft_prog_name(int fd, char *prog_name);
char					*ft_prog_comment(int fd, char *comment);
unsigned char			*ft_read_op(int fd, int size);
void					ft_validation_arg(char **params, t_mstruc *inst, int i);
char					*ft_create_new_player(int i, char **params,
						t_mstruc *inst);
int						ft_file_extension(char *str);
char					*ft_num_player(int *ind, char **params,
						t_mstruc *inst, int i);
char					*ft_check_repeat_num(t_mstruc *inst);
void					ft_give_num(t_players *ptr, int i, int j,
						t_mstruc *inst);
int						ft_give_num_help(t_mstruc *inst);
void					ft_core_war_viz(t_mstruc *inst, int live_flag);
void					ft_choose_one(t_mstruc *inst);
int						ft_begin_vis(t_mstruc *inst, t_draw *draw);
void					ft_winner(t_mstruc *inst);
void					ft_cycle_to_die(t_process *lst, t_mstruc *inst,
						int *live_flag);
void					ft_core_war(t_mstruc *inst, int live_flag);
void					ft_create_process(t_mstruc *inst);
void					ft_fill_opcode_mem(t_mstruc *inst);
int						ft_opcode(int pc, t_mstruc *inst, t_process *process);
int						ft_validate_coding_byte(t_process *process);
void					ft_fill_param_size(t_opcode *op_lst);
int						ft_fill_param(t_opcode *op_lst, t_mstruc *inst,
						int *ind, t_process *pr);
int						ft_type_param(t_opcode *op_lst, int nam_arg,
						unsigned char *test_byte);
int						ft_type_param_3(t_opcode *op_lst,
						unsigned char *test_byte);
int						ft_type_param_2(t_opcode *op_lst,
						unsigned char *test_byte);
int						ft_type_param_1(t_opcode *op_lst,
						unsigned char *test_byte);
int						ft_var_param(t_opcode *op_lst, int nam_arg);
int						ft_third_param(t_opcode *op_lst, int num);
int						ft_second_param(t_opcode *op_lst, int num);
int						ft_first_param(t_opcode *op_lst, int num);
void					ft_validate_opcode(t_process *process,
						t_mstruc *inst, int flag);
void					ft_validate_comand(t_process *process, t_mstruc *inst);
void					ft_write_contestants(int i, char *str, t_players *pl);
void					ft_write_winner(t_players *player);
void					output_dump(t_mstruc *ms);
void					output_dump2(int j);
char					*ft_itoa_base(uintmax_t n, long long int base);
int						ft_count_base(uintmax_t nb, long long int base);
char					*ft_itoa_memory(uintmax_t n, long long int base);
int						get_pc(int pc);
t_process				*copy_process(t_process *rhs);
void					new_process(t_process *rpr, t_mstruc *ms, int pc);
t_process				*delete_process(t_process *pr, t_mstruc *ms);
void					value_to_memory(t_mstruc *ms, int pos, int val);
void					live_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					ld_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					st_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					add_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					sub_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					and_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					or_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					xor_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					zjmp_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					ldi_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					sti_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					fork_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					lld_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					lldi_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					lfork_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
void					aff_com(t_mstruc *ms, t_process *pr, t_opcode *arg);
int						ft_check_first(t_mstruc *ms, t_process *pr,
						t_opcode *arg, int idx);
int						ft_check_param(t_mstruc *ms, t_process *pr,
						t_opcode *arg, int idx);
void					init_operators();
void					ft_comands(t_mstruc *ms, t_process *pr, t_opcode *arg);

#endif
