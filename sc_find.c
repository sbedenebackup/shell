#include "sc_script.h"

int	find_ft(char *line)
{
	if (!ft_strcmp(line, "cd"))
		return (FT_CD);
	else if (!ft_strcmp(line, "echo"))
		return (FT_ECHO);
	else if (!ft_strcmp(line, "exit"))
		return (FT_EXIT);
	else if (!ft_strcmp(line, "type"))
		return (FT_TYPE);
	else if (!ft_strcmp(line, "alias"))
		return (FT_ALS);
	else if (!ft_strcmp(line, "unalias"))
		return (FT_UNALS);
	else if (!ft_strcmp(line, "hash"))
		return (FT_HASH);
	return (FT_NONE);
}

int	find_kw(char *line, t_script *script)
{
	//printf("%s\n", line);
	if (!ft_strcmp(line, "if"))
		return (KW_IF);
	else if (!ft_strcmp(line, "elif"))
		return (KW_ELIF);
	else if (!ft_strcmp(line, "else"))
		return (KW_ELSE);
	else if (!ft_strcmp(line, "then"))
		return (KW_THEN);
	else if (!ft_strcmp(line, "fi"))
		return (KW_FI);
	else if (!ft_strcmp(line, "for"))
		return (KW_FOR);
	else if (!ft_strcmp(line, "in") && script->last_kw == KW_FOR)
		return (KW_FIN);
	else if (!ft_strcmp(line, "while"))
		return (KW_WHL);
	else if (!ft_strcmp(line, "break"))
		return (KW_BRK);
	else if (!ft_strcmp(line, "continue"))
		return (KW_CNT);
	else if (!ft_strcmp(line, "do"))
		return (KW_DO);
	else if (!ft_strcmp(line, "done"))
		return (KW_DONE);
	else if (!ft_strcmp(line, "case"))
		return (KW_CASE);
	else if (!ft_strcmp(line, "esac"))
		return (KW_ESAC);
	else if (!ft_strcmp(line, "in") && script->last_kw == KW_CASE)
		return (KW_CIN);
	return (KW_NONE);
}

t_script	*update_next(t_script *script, int kw)
{
	if (kw == KW_NONE)
		return (none_next(script));
	else if (kw == KW_IF)
		return (if_next(script));
	else if (kw == KW_ELIF)
		return (if_next(script));
	else if (kw == KW_ELSE)
		return (else_next(script));
	else if (kw == KW_THEN)
		return (then_next(script));
	else if (kw == KW_FI)
		return (fi_next(script));
	else if (kw == KW_FOR || kw == KW_WHL)
		return (loop_next(script));
	else if (kw == KW_FIN)
		return (fin_next(script));
	else if (kw == KW_BRK || kw == KW_CNT || kw == KW_DONE || kw == KW_ESAC)
		return (ctrl_next(script));
	else if (kw == KW_DO)
		return (do_next(script));
	else if (kw == KW_CASE)
		return (case_next(script));
	else if (kw == KW_CIN)
		return (cin_next(script));
	return (script);
}

char	*kw_to_str(int kw)
{
	if (kw == KW_NONE)
		return ("none");
	else if (kw == KW_IF)
		return ("if");
	else if (kw == KW_ELIF)
		return ("elif");
	else if (kw == KW_ELSE)
		return ("else");
	else if (kw == KW_THEN)
		return ("then");
	else if (kw == KW_FI)
		return ("fi");
	else if (kw == KW_FOR)
		return ("for");
	else if (kw == KW_FIN)
		return ("in");
	else if (kw == KW_WHL)
		return ("while");
	else if (kw == KW_BRK)
		return ("break");
	else if (kw == KW_CNT)
		return ("continue");
	else if (kw == KW_DO)
		return ("do");
	else if (kw == KW_DONE)
		return ("done");
	else if (kw == KW_ESAC)
		return ("esac");
	else if (kw == KW_CASE)
		return ("case");
	else if (kw == KW_CIN)
		return ("in");
	return ("error");
}