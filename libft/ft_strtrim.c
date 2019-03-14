/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:42:54 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 17:32:05 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*p;
	char	*fresh;
	int		m;
	int		n;

	m = 0;
	n = 0;
	if (!s)
		return (NULL);
	p = (char*)s;
	while (ft_isspace(*p))
		p++;
	while (p[m])
	{
		if ((ft_isspace(p[m + 1]) || p[m + 1] == '\0') && !ft_isspace(p[m]))
			n = m;
		m++;
	}
	fresh = ft_strsub(p, 0, n + 1);
	return (fresh);
}
