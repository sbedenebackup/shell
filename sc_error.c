#include "sc_script.h"

void    expected(t_script *script, int kw)
{
	ft_putstr("Expected \'");
	ft_putstr(kw_to_str(kw));
	ft_putstr("\' after \'");
	ft_putstr(kw_to_str(script->last_kw));
	ft_putstr("\' on line ");
	ft_putnbr(script->line_nb);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void    unexpected(t_script *script, int kw)
{
	ft_putstr("Unexpected \'");
	ft_putstr(kw_to_str(kw));
	ft_putstr("\' on line ");
	ft_putnbr(script->line_nb);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void	error(t_script *script, int kw)
{
	int	i;

	i = -1;
	while (++i < KW_NB)
		if (script->next_kw[i] == 1)
			break ;
		else if (script->next_kw[i] == 2)
            expected(script, i);
    unexpected(script, kw);
}
