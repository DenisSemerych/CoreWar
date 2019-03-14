/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:26:18 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 13:52:37 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(char *base)
{
	int n;
	int m;
	int good;

	n = 0;
	good = 1;
	while (base[n])
	{
		m = n + 1;
		while (base[m])
			if (base[m++] == base[n])
				good = 0;
		if (good == 0 || base[n] == '-' || base[n] == '+')
			return (0);
		n++;
	}
	return (1);
}

static int	ft_check_data(char *num, char *base)
{
	int n;
	int m;
	int good;

	if (!ft_check_base(base))
		return (0);
	m = 0;
	while (num[m++])
	{
		good = 0;
		n = 0;
		while (base[n])
			if (num[m - 1] == base[n++])
				good = 1;
		if (good == 0)
			return (0);
	}
	return (n);
}

static int	ft_getnum(char num, char *base)
{
	int n;

	n = 0;
	while (base[n])
	{
		if (num == base[n])
			return (n);
		n++;
	}
	return (n);
}

int			ft_atoi_base(char *num, char *base)
{
	int			bs;
	long int	nb;
	int			sign;

	sign = 1;
	nb = 0;
	while (ft_isspace(*num))
		num++;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	if (!num || !base || (bs = ft_check_data(num, base)) < 2)
		return (0);
	while (*num)
		nb = nb * bs + ft_getnum(*num++, base);
	return ((int)(nb *= sign));
}
