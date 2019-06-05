/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:43:01 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 15:56:41 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int cpt;
	int ghost_cpt;

	cpt = 0;
	if (!needle || needle[0] == '\0')
		return ((char*)haystack);
	while (haystack && haystack[cpt] != '\0')
	{
		if (haystack[cpt] == needle[0])
		{
			ghost_cpt = 0;
			while (needle[ghost_cpt] != '\0')
			{
				if (needle[ghost_cpt] != haystack[cpt + ghost_cpt])
					break ;
				ghost_cpt++;
			}
			if (needle[ghost_cpt] == '\0')
				return ((char*)haystack + cpt);
		}
		cpt++;
	}
	return (NULL);
}
