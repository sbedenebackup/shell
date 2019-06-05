#include "sc_script.h"

t_script	*reset_next(t_script *script)
{
	int	i;

	i = -1;
	while (++i < KW_NB)
		script->next_kw[i] = 0;
	return (script);
}

t_script	*none_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CASE] = 1;
	return (script);
}

t_script	*loop_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_DO] = 2;
	return (script);
}

t_script	*if_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_THEN] = 2;
	return (script);
}

t_script	*elif_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_ELIF] = 1;
	script->next_kw[KW_ELSE] = 1;
	script->next_kw[KW_FI] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

t_script	*else_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_FI] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

t_script 	*then_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_ELIF] = 1;
	script->next_kw[KW_ELSE] = 1;
	script->next_kw[KW_FI] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

t_script 	*fi_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_ELIF] = 1;
	script->next_kw[KW_ELSE] = 1;
	script->next_kw[KW_FI] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_DONE] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

t_script	*do_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_DONE] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

/*
 * control: break, continue, done, esac
 */

t_script	*ctrl_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_FI] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_DONE] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}

t_script	*case_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_CIN] = 2;
	return (script);
}

t_script	*fin_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_DO] = 2;
	return (script);
}

t_script 	*cin_next(t_script *script)
{
	script = reset_next(script);
	script->next_kw[KW_IF] = 1;
	script->next_kw[KW_FOR] = 1;
	script->next_kw[KW_BRK] = 1;
	script->next_kw[KW_WHL] = 1;
	script->next_kw[KW_CNT] = 1;
	script->next_kw[KW_CASE] = 1;
	script->next_kw[KW_ESAC] = 1;
	return (script);
}
