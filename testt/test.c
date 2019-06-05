
# define CD_EQ		0
# define CD_GT		1
# define CD_GTE		2
# define CD_LT		3
# define CD_LTE		4

# define KW_WHL		1
# define KW_IF		2
# define KW_ELIF	3
# define KW_ELSE	4
# define T_INSTR	5

#include "sc_script.h"

typedef struct		s_tree
{
	int		type;
	char		*left;
	int		op;
	char		*right;
	char		*instr;
	struct s_tree 	*true;
	struct s_tree	*false;
	struct s_tree	*next;
}			t_tree;

int main(void)
{
	t_tree *begin;
	t_tree *fifty;
	t_tree *exit;
	t_tree *exec;

	exit = (t_tree *)malloc(sizeof(t_tree));
	exit->type = T_INSTR;
	exit->left = NULL;
	exit->op = 0;
	exit->right = NULL;
	exit->instr = ft_strdup("exit(EXIT_SUCCESS)");
	exit->true = NULL;
	exit->false = NULL;
	exit->next = NULL;

	fifty = (t_tree *)malloc(sizeof(t_tree));
	fifty->type = T_INSTR;
	fifty->left = NULL;
	fifty->op = 0;
	fifty->right = NULL;
	fifty->instr = ft_strdup("echo ok");
	fifty->true = NULL;
	fifty->false = NULL;
	fifty->next = exit;

	begin = (t_tree *)malloc(sizeof(t_tree));
	begin->type = KW_WHL;
	begin->left = ft_strdup("50");
	begin->op = CD_EQ;
	begin->right = ft_strdup("0");
	begin->instr = NULL;
	begin->true = fifty;
	begin->false = exit;

	exec = begin;
	while (exec)
	{
		if (exec->type == KW_WHL)
		{
			if (exec->op == CD_EQ)
			{
				if (ft_atoi(exec->left) == ft_atoi(exec->right))
					exec = exec->true;
				else
					exec = exec->false;
			}
		}
		else if (exec->type == T_INSTR)
		{
			if (exec->instr)
				printf("%s\n", exec->instr);
			exec = exec->next;
		}
	}
}
