/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lssort_revfunc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:31:48 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:33:29 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

int		ft_lssort_lexrev(t_train *node, t_train *node2)
{
	if (node->file.path && node2->file.path)
		return (ft_strcmp(node->file.path, node2->file.path) > 0);
	else
		return (ft_strcmp(node->file.filename, node2->file.filename) > 0);
}

int		ft_lssort_timerev(t_train *node, t_train *node2)
{
	if (node->file.stat.st_mtimespec.tv_sec ==
			node2->file.stat.st_mtimespec.tv_sec)
	{
		if (node->file.stat.st_mtimespec.tv_nsec ==
				node2->file.stat.st_mtimespec.tv_nsec)
			return (ft_lssort_lexrev(node, node2));
		else
			return (node->file.stat.st_mtimespec.tv_nsec <
					node2->file.stat.st_mtimespec.tv_nsec);
	}
	return ((node->file.stat.st_mtimespec.tv_sec <
				node2->file.stat.st_mtimespec.tv_sec));
}

int		ft_lssort_sizerev(t_train *node, t_train *node2)
{
	if (node->file.stat.st_size == node2->file.stat.st_size)
		return (ft_lssort_lexrev(node, node2));
	return (node->file.stat.st_size < node2->file.stat.st_size);
}
