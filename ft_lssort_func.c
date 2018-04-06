/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lssort_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 05:59:47 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:45:43 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

/*
** Sort t_lsfunction notice
** All sort t_lsfunction must return true when element is in right order and
** false otherwise
*/

int			ft_lssort_lexicographical(t_train *node, t_train *node2)
{
	if (node->file.path && node2->file.path)
		return (ft_strcmp(node->file.path, node2->file.path) < 0);
	else
		return (ft_strcmp(node->file.filename, node2->file.filename) < 0);
}

int			ft_lstsort_time(t_train *node, t_train *node2)
{
	if (node->file.stat.st_mtimespec.tv_sec ==
			node2->file.stat.st_mtimespec.tv_sec)
	{
		if (node->file.stat.st_mtimespec.tv_nsec ==
				node2->file.stat.st_mtimespec.tv_nsec)
			return (ft_lssort_lexicographical(node, node2));
		else
			return (node->file.stat.st_mtimespec.tv_nsec >
					node2->file.stat.st_mtimespec.tv_nsec);
	}
	return ((node->file.stat.st_mtimespec.tv_sec >
				node2->file.stat.st_mtimespec.tv_sec));
}

int			ft_lssort_size(t_train *node, t_train *node2)
{
	if (node->file.stat.st_size == node2->file.stat.st_size)
		return (ft_lssort_lexicographical(node, node2));
	return (node->file.stat.st_size > node2->file.stat.st_size);
}

t_lsfunc	ft_getsort(t_lsflags flag)
{
	if (flag.f)
		return (NULL);
	if (flag.r)
	{
		if (flag.size)
			return (&ft_lssort_sizerev);
		else if (flag.t)
			return (&ft_lssort_timerev);
		else if (flag.lex)
			return (&ft_lssort_lexrev);
	}
	else
	{
		if (flag.size)
			return (&ft_lssort_size);
		else if (flag.t)
			return (&ft_lstsort_time);
		else if (flag.lex)
			return (&ft_lssort_lexicographical);
	}
	return (NULL);
}
