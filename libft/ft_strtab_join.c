/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtab_join.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:21:09 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:25:54 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtab_join(char ***tab, char *str)
{
	int             i;
	char    **new_tab;

	i = 0;
	while (*tab && (*tab)[i])
		i++;
	if (!(new_tab = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	i = -1;
	while (*tab && (*tab)[++i])
		new_tab[i] = (*tab)[i];
	i = i == -1 ? 0 : i;
	if (!(new_tab[i++] = ft_strdup(str)))
		return (0);
	new_tab[i] = NULL;
	if (*tab)
		free(*tab);
	*tab = new_tab;
	return (1);
}
