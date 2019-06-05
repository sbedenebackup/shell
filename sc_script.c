#include "sc_script.h"

/*
 * functions to get next compatible keywords
 */

t_script	*init_script(void)
{
	t_script	*script;

	script = (t_script *)malloc(sizeof(t_script));
	script = reset_next(script);
	script->last_kw = KW_NONE;
	script = none_next(script);
	script->line_nb = 1;
	script->curr_node = NULL;
	script->tree = NULL;
	script->kw_head = NULL;
	script->kw_tail = NULL;
	script->rbp = NULL;
	script->rsp = NULL;
	script->functions = NULL;
	return (script);
}

/*
 * parse program line into keyword, comment or instruction
 */

int	sc_get_type(char *line)
{
	int	i;

	line = ft_strtrim(line);
	if (line[0] == '#')
		return (T_CMT);
	else if (line[0] == '\0')
		return (-1);
	i = -1;
	while (line[++i])
	{
		//modifier par find variable
		if ((i == 0 && ft_isdigit(line[i])) || (!ft_isalnum(line[i]) && line[i] != '_' && line[i] != '=' && line[i] != '[' && line[i] != ']' && line[i] != '$'))
			return (T_KW);
		else if (line[i] == '=')
			return (T_INSTR);
	}
	return (T_KW);
} 
		
/*
 * main function which parses a program line into tokens
 */

void	print_queue(t_kwqueue *queue)
{
	t_kwqueue *curr;

	curr = queue;
	while (curr)
	{
		printf("%s => ", kw_to_str(curr->kw));
		curr = curr->next;
	}
	printf("\n");
}

t_script	*grow_tree(t_script *script, int kw, char *line)
{
	t_tree	*curr;

	// print_queue(script->kw_head);
	if (script->kw_tail)
		curr = script->kw_tail->node;
	if (is_ctrl_end(kw))
	{
		// printf(">>> ctrl end\n");
		script = pop_kw(script);
		;
	}
	else if (is_new_cond(kw))
	{
		// printf(">>> new cond\n");
		if (!script->curr_node)
			script = push_kw(script, kw, D_NONE);
		else if (script->curr_node->type == T_INSTR)
			script = push_kw(script, kw, D_NEXT);
		else if (script->curr_node->type == T_KW)
			script = push_kw(script, kw, D_TRUE);
	}
	else if (is_secondary_cond(kw))
	{
		// printf(">>> second cond\n");
		// printf("%s\n", kw_to_str(script->kw_tail->node->kw));
		script = pop_kw(script);
		script = add_cond(script, kw);
		curr->next = script->kw_tail->node;
		// printf("%s => %s\n", kw_to_str(curr->kw), kw_to_str(curr->next->kw));
	}
	else if (script->curr_node && script->curr_node->type == T_KW && is_ctrl_start(script->last_kw))
	{
		// printf(">>> true\n");
		script = add_true(script, line);
	}
	else if (!script->curr_node || script->curr_node->type == T_INSTR || is_ctrl_end(script->last_kw))
	{
		// printf(">>> next\n");
		script = add_next(script, line);
	}
	else
		;
		// printf(">>> none\n");
	if (is_ctrl_end(script->last_kw))
	{
		printf("%s\n", kw_to_str(script->curr_node->kw));
		curr->next = script->curr_node;
	}
	return (script);
}

void		dump_script(t_script *script)
{
	t_tree		*curr_node;
	t_kwqueue	*queue;

	curr_node = script->curr_node;
	queue = script->kw_head;
	// printf(">> last_kw: %s\n\n", kw_to_str(script->last_kw));
	if (curr_node && curr_node->type == T_KW)
	{
		// printf(">> curr_node: KW\n");
		// printf(">> >> kw: %s\n", kw_to_str(curr_node->kw));
		if (curr_node->true)
		{
			// printf(">> >> true:\n");
			if (curr_node->true->type == T_KW)
			{
				;
				// printf(">> >> >> kw: %s\n", kw_to_str(curr_node->true->kw));
			}
			else
			{
				;
				// printf(">> >> >> instr: %s\n", curr_node->true->instr);
			}
		}
		if (curr_node->next)
		{
			// printf(">> >> next:\n");
			if (curr_node->next->type == T_KW)
			{
				;
				// printf(">> >> >> kw: %s\n", kw_to_str(curr_node->next->kw));
			}
			else
			{
				;
				// printf(">> >> >> instr: %s\n", curr_node->next->instr);
			}
		}
	}
	// printf("\n");
	if (queue)
	{
		// printf(">> queue:\n>> >> ");
		while (queue)
		{
			// printf("%s - ", kw_to_str(queue->kw));
			queue = queue->next;
		}
	}
	// printf("\n\n ");
}

t_script	*set_kw(t_script *script, char *line, int type)
{
	unsigned long	len;
	int	kw;
	int	i;
	char	**tokens;

	line = ft_strtrim(line);
	tokens = ft_strsplit(line, ' ');
	i = -1;
	while (tokens[++i])
	{
		// printf("\n%s\n", tokens[i]);
		if (tokens[i][0] == '#')
			return (script);
		len = ft_strlen(tokens[i]);
		kw = find_kw(tokens[i], script);
		// if (is_new_cond(kw) || is_secondary_cond(kw) || is_ctrl_start(kw) || is_ctrl_end(kw))
		// {
		// printf("\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvDUMP SCRIPTvvvvvvvvvvvvvvvvv\n");
		// dump_script(script);
		// }
		script = grow_tree(script, kw, line);
		// if (is_new_cond(kw) || is_secondary_cond(kw) || is_ctrl_start(kw) || is_ctrl_end(kw))
		// printf("\n------------------------------\n");
		// if (is_new_cond(kw) || is_secondary_cond(kw) || is_ctrl_start(kw) || is_ctrl_end(kw))
		// dump_script(script);
		if (kw == KW_NONE)
		{
			if (find_ft(tokens[i]) != FT_NONE)
			       return (script);
			else if (i == 0)
			{
				// ft_putstr(tokens[i]);
				// ft_putendl(" not found.");
				return (script);
			}
			else
				continue ;
		}
		if (script->next_kw[kw] < 1)
			error(script, kw);
		// printf("%s %s\n", kw_to_str(script->last_kw), kw_to_str(kw));
		// if (is_new_cond(kw) || is_secondary_cond(kw) || is_ctrl_start(kw) || is_ctrl_end(kw))
		// printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ENDDUMP^^^^^^^^^^^^^^\n");
		script = reset_next(script);
		script->last_kw = kw;
		script = update_next(script, kw);
	}
	return (script);	
}

void	print_tree(t_tree *node)
{
	printf("%s [%s] ", node->type == T_KW ? "kw" : "instr", node->type == T_KW ? kw_to_str(node->kw) : node->instr);
	if (node->true)
	{
		printf(">> true >> ");
		printf("%s [%s] ", node->true->type == T_KW ? "kw" : "instr", node->true->type == T_KW ? kw_to_str(node->true->kw) : node->true->instr);
	}
	if (node->next)
	{
		printf(">> next >> ");
		printf("%s [%s] ", node->next->type == T_KW ? "kw" : "instr", node->next->type == T_KW ? kw_to_str(node->next->kw) : node->next->instr);
	}
	printf("\n\n");
	if (node->true)
		print_tree(node->true);
	if (node->next)
		print_tree(node->next);
}

int main(int ac, char **av)
{
	t_script	*script;
	int	fd;
	char	*line;

	script = init_script();
	fd = open(av[1], O_RDONLY);
	line = (char *)malloc(sizeof(char));
	line[0] = '\0';
	while (get_next_line(fd, &line) > 0)
	{
		//printf("%s\n", line);
		script = set_kw(script, line, sc_get_type(line));
		script->line_nb++;
	}
	print_tree(script->tree);
	sc_exec(script);
	// check si kwqueue est vide (au cas ou \"if then\" sans fi en fin de fichier)
}
