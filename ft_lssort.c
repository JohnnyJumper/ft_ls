/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lssort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:07:50 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:34:58 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

static void		ft_lssort_winit(t_train *worker[], t_train *end,
		t_train *head)
{
	worker[pivot] = end;
	M_N(worker[previous]);
	worker[current] = head;
	worker[tail] = worker[pivot];
}

static void		ft_lssort_partition_helper(t_train *worker[])
{
	t_train *tmp;

	tmp = worker[current]->next;
	worker[current]->next = NULL;
	worker[tail]->next = worker[current];
	worker[tail] = worker[current];
	worker[current] = tmp;
}

static t_train	*ft_lssort_partition(t_train *head, t_train *end,
		t_train *new[], t_lsfunc sort_t_lsfunction)
{
	t_train		*worker[all];

	ft_lssort_winit(worker, end, head);
	while (worker[current] != worker[pivot])
	{
		if (sort_t_lsfunction(worker[current], worker[pivot]))
		{
			if (new[new_head] == NULL)
				new[new_head] = worker[current];
			worker[previous] = worker[current];
			worker[current] = worker[current]->next;
		}
		else
		{
			if (worker[previous])
				worker[previous]->next = worker[current]->next;
			ft_lssort_partition_helper(worker);
		}
	}
	if (new[new_head] == NULL)
		new[new_head] = worker[pivot];
	new[new_end] = worker[tail];
	return (worker[pivot]);
}

t_train			*ft_lssort_recur(t_train *head, t_train *end,
		t_lsfunc sort_t_lsfunction)
{
	t_train		*new[2];
	t_train		*pivot;
	t_train		*tmp;

	MAKE_NULL3(new[new_end], new[new_head], tmp);
	if (!sort_t_lsfunction)
		return (head);
	if (!head || head == end)
		return (head);
	pivot = ft_lssort_partition(head, end, new, sort_t_lsfunction);
	if (new[new_head] != pivot)
	{
		tmp = new[new_head];
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		new[new_head] = ft_lssort_recur(new[new_head], tmp, sort_t_lsfunction);
		tmp = ft_trainget_tail(new[new_head]);
		tmp->next = pivot;
	}
	pivot->next = ft_lssort_recur(pivot->next, new[new_end], sort_t_lsfunction);
	return (new[new_head]);
}

void			ft_lssort(t_train **root, t_lsmain *main)
{
	*root = ft_lssort_recur(*root, ft_trainget_tail(*root),
			ft_getsort(main->flag));
}
