/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_auxiliary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 01:01:39 by yochered          #+#    #+#             */
/*   Updated: 2019/03/26 01:49:10 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	ft_lstdelcrt(t_list **list, t_list *to_delete)
{
	t_list	*p;

	if (!list || !*list || !to_delete)
		return ;
	if (*list == to_delete)
		*list = (*list)->next;
	else
	{
		p = *list;
		while (p->next != to_delete)
			p = p->next;
		p->next = to_delete->next;
	}
	free(to_delete->content);
	free(to_delete);
}

void	insert_champ(t_data *data, t_champ *champ)
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*prev_next;

	new_lst = ft_lstnew(0, 0);
	if ((new_lst->content = champ) == champ && data->champs == NULL)
	{
		ft_lstadd(&(data->champs), new_lst);
		return ;
	}
	else if (data->champs->next == NULL)
	{
		if (((t_champ *)(data->champs->content))->number > champ->number)
			ft_lstadd(&(data->champs), new_lst);
		else
			data->champs->next = new_lst;
		return ;
	}
	tmp = data->champs;
	while (tmp->next &&
		((t_champ *)(tmp->next->content))->number < champ->number)
		tmp = tmp->next;
	prev_next = tmp->next;
	tmp->next = new_lst;
	new_lst->next = prev_next;
}

int		is_playing_check(t_data *data)
{
	t_list	*process;

	if (!data->processes)
		data->playing = 0;
	else
	{
		process = data->processes;
		while (process)
		{
			if (((t_process *)process->content)->live)
				return (data->playing = 1);
			process = process->next;
		}
		data->playing = 0;
	}
	return (data->playing);
}

t_list	*delete_process(t_data *d, t_list *process)
{
	t_process	*p;
	t_list		*next;

	p = (t_process*)process->content;
	if (d->n_flag & 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				p->uniq_number, d->cycle - p->alive_cycle, d->cycle_to_die);
	next = process->next;
	ft_lstdelcrt(&d->processes, process);
	return (next);
}

void	to_die_check(t_data *d)
{
	t_list		*process;
	t_process	*p;

	process = d->processes;
	while (process)
	{
		p = (t_process*)process->content;
		if (d->cycle - p->alive_cycle >= d->cycle_to_die)
			process = delete_process(d, process);
		else
			process = process->next;
	}
	if (d->live_op_amount >= NBR_LIVE || ++d->checks_amount >= MAX_CHECKS)
	{
		d->cycle_to_die -= CYCLE_DELTA;
		d->checks_amount = 0;
		if (d->n_flag & 2)
			ft_printf("Cycle to die is now %d\n", d->cycle_to_die);
	}
	d->cycles_fr_lst_check = 0;
	d->live_op_amount = 0;
}
