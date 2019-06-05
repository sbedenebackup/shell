#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

#ifndef SC_SCRIPT_H
# define SC_SCRIPT_H

# define T_KW		101
# define T_FT		102
# define T_INSTR	103
# define T_CMT		104 

# define KW_NB		19
# define KW_NONE	0
# define KW_IF		1
# define KW_ELIF	2
# define KW_ELSE	3
# define KW_THEN	4
# define KW_FI		5
# define KW_FOR		6
# define KW_FIN		7
# define KW_WHL		8
# define KW_BRK		9
# define KW_CNT		10
# define KW_DO		11
# define KW_DONE	12
# define KW_ESAC	13
# define KW_CASE	14
# define KW_CIN		15
# define KW_SLCT	16
# define KW_UNTL	17
# define KW_TIME	18

# define FT_NONE	200
# define FT_CD		201
# define FT_ECHO	202
# define FT_EXIT	203
# define FT_TYPE	204
# define FT_ALS		205
# define FT_UNALS	206
# define FT_HASH	207

# define OP_EQ		0
# define OP_NEQ		1
# define OP_GT		2
# define OP_GTE		3
# define OP_LT		4
# define OP_LTE		5

# define D_NONE		0
# define D_TRUE		1
# define D_NEXT		2

typedef struct			s_stack
{
	int					ar_length;
	char				*var;
	char				*val;
	struct s_stack		*up;
	struct s_stack		*down;
}						t_stack;

typedef struct			s_tree
{
	int					type;
	int					kw;
	char				*lhs;
	int					op;
	char				*rhs;
	char				*instr;
	struct s_tree		*true;
	struct s_tree		*next;
}						t_tree;

typedef struct			s_kwqueue
{
	int					kw;
	t_tree				*node;
	struct s_kwqueue	*next;
	struct s_kwqueue	*prev;
}						t_kwqueue;

typedef struct			s_functions
{
	char				*name;
	t_tree				*tree;
	struct s_function	*next;
}						t_functions;

typedef struct			s_script
{
	int					last_kw;
	int					next_kw[KW_NB];
	int					line_nb;
	int					next_type;
	t_tree				*curr_node;
	t_tree				*tree;
	t_kwqueue			*kw_head;
	t_kwqueue			*kw_tail;
	t_stack				*rbp;
	t_stack				*rsp;
	t_functions			*functions;
}						t_script;

t_script				*reset_next(t_script *script);
t_script				*none_next(t_script *script);
t_script				*loop_next(t_script *script);
t_script				*if_next(t_script *script);
t_script				*elif_next(t_script *script);
t_script				*else_next(t_script *script);
t_script 				*then_next(t_script *script);
t_script 				*fi_next(t_script *script);
t_script				*do_next(t_script *script);
t_script				*ctrl_next(t_script *script);
t_script				*case_next(t_script *script);
t_script				*fin_next(t_script *script);
t_script 				*cin_next(t_script *script);

int						find_ft(char *line);
int						find_kw(char *line, t_script *script);
t_script				*update_next(t_script *script, int kw);
char					*kw_to_str(int kw);

void					error(t_script *script, int kw);

int						is_new_cond(int kw);
int						is_secondary_cond(int kw);
int						is_ctrl_start(int kw);
int						is_ctrl_end(int kw);
t_script				*push_kw(t_script *script, int kw, int door);
t_script				*pop_kw(t_script *script);
t_script				*add_true(t_script *script, char *line);
t_script				*add_next(t_script *script, char *instr);
t_script				*add_false(t_script *script, char *line);
t_script				*add_cond(t_script *script, int kw);

void    				sc_exec(t_script *script);

#endif
