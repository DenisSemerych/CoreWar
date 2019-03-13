/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:48:47 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/03/13 16:10:55 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	n;
	int				temp;

	n = 0;
	while (n < size - 1)
	{
		if (tab[n] > tab[n + 1])
		{
			temp = tab[n];
			tab[n] = tab[n + 1];
			tab[n + 1] = temp;
			if (n > 0)
				n = n - 2;
		}
		n++;
	}
}
