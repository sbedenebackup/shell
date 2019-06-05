#include "sc_script.h"

int 		is_new_cond(int kw)
{
	if (kw == KW_IF || kw == KW_FOR || kw == KW_WHL
	|| kw == KW_CASE)
		return (1);
	return (0);
}

int			is_secondary_cond(int kw)
{
	if (kw == KW_ELIF || kw == KW_ELSE)
		return (1);
	return (0);
}

int			is_ctrl_start(int kw)
{
	if (kw == KW_THEN || kw == KW_FIN || kw == KW_CIN
	|| kw == KW_DO || kw == KW_ELSE)
		return (1);
	return (0);
}

int			is_ctrl_end(int kw)
{
	if (kw == KW_FI || kw == KW_DONE || kw == KW_ESAC)
		return (1);
	return (0);
}

t_tree		*new_node(void)
{
	t_tree		*elem;

	elem = (t_tree *)malloc(sizeof(t_tree));
	elem->type = -1;
	elem->kw = KW_NONE;
	elem->lhs = NULL;
	elem->op = -1;
	elem->rhs = NULL;
	elem->instr = NULL;
	elem->true = NULL;
	elem->next = NULL;
	return (elem);
}

t_tree		*new_kwnode(int kw)
{
	t_tree	*elem;

	elem = new_node();
	elem->type = T_KW;
	elem->kw = kw;
	return (elem);
}

t_tree		*new_instrnode(char *instr)
{
	t_tree	*elem;

	elem = new_node();
	elem->type = T_INSTR;
	elem->instr = instr;
	return (elem);
}

t_kwqueue	*new_kw(int kw, t_kwqueue *prev)
{
	t_kwqueue	*elem;

	elem = (t_kwqueue *)malloc(sizeof(t_kwqueue));
	elem->kw = kw;
	elem->node = new_kwnode(kw);
	elem->next = NULL;
	elem->prev = prev;
	return (elem);
}

t_script	*pop_kw(t_script *script)
{
	t_kwqueue	*prev;

	prev = script->kw_tail->prev;
	if (!prev)
	{
		script->kw_head = NULL;
		free(script->kw_tail);
	}
	script->kw_tail = prev;
	if (prev)
		script->curr_node = script->kw_tail->node;
	return (script);
}

t_script	*push_kw(t_script *script, int kw, int door)
{
	t_kwqueue	*curr;

	curr = script->kw_tail;
	script->kw_tail = new_kw(kw, script->kw_tail);
	if (curr)
		curr->next = script->kw_tail;
	if (!script->kw_head)
		script->kw_head = script->kw_tail;
	if (door == D_NEXT)
		script->curr_node->next = script->kw_tail->node;
	else if (door == D_TRUE)
		script->curr_node->true = script->kw_tail->node;
	script->curr_node = script->kw_tail->node;  
	if (!script->tree)
		script->tree = script->curr_node;
	return (script);
}

t_script	*add_true(t_script *script, char *instr)
{
	script->kw_tail->node->true = new_instrnode(instr);
	script->curr_node = script->kw_tail->node->true;
	return (script);
}

t_script	*add_next(t_script *script, char *instr)
{
	if (!script->curr_node)
	{
		script->curr_node = new_instrnode(instr);
		script->tree = script->curr_node;
	}
	else
	{
		script->curr_node->next = new_instrnode(instr);
		script->curr_node = script->curr_node->next;
	}
	return (script);
}

t_script	*add_false(t_script *script, char *line)
{
	return (script);
}

t_script	*add_cond(t_script *script, int kw)
{
	t_kwqueue	*curr;

	script = push_kw(script, kw, D_NEXT);
	return (script);
}