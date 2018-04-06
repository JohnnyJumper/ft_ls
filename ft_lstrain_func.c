/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrain_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 01:18:16 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/12 20:56:53 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_train		*ft_train_pop(t_train **root)
{
	t_train		*result;

	if (!(*root))
		return (NULL);
	result = *root;
	*root = (*root)->next;
	return (result);
}

void		ft_lstrain_add(t_train **root, t_train *new_train)
{
	if (!new_train)
		return ;
	if (*root)
		new_train->next = *root;
	*root = new_train;
}

t_train		*ft_trainget_tail(t_train *root)
{
	while (root != NULL && root->next != NULL)
		root = root->next;
	return (root);
}

void		ft_traindel(t_train **root)
{
	t_train		*current;
	t_train		*next;

	current = *root;
	while (current)
	{
		next = current->next;
		ft_trainfree(&current);
		current = next;
	}
	*root = NULL;
}
