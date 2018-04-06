/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 09:29:47 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/13 00:22:44 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

static int	ft_filename_check(t_train **new_train)
{
	if (ft_strlen((*new_train)->file.filename) > 1024)
	{
		printf("ft_ls: %s File name too long.\n", (*new_train)->file.filename);
		ft_memdel((void **)&(*new_train)->file.filename);
		ft_memdel((void **)&new_train);
		return (1);
	}
	return (0);
}

static int	ft_checkerror(int error, t_train **new_train, char *filename)
{
	if (error == -1)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", filename);
		ft_memdel((void **)&(*new_train)->file.filename);
		ft_memdel((void **)new_train);
		return (1);
	}
	return (0);
}

t_train		*ft_lstrain_create(char *file, char *path)
{
	t_train			*new_train;
	int				error;
	char			*tmp;

	new_train = (t_train *)ft_memalloc(sizeof(t_train));
	new_train->file.filename = ft_strnew(ft_strlen(file));
	ft_strcpy(new_train->file.filename, file);
	tmp = new_train->file.path;
	if (ft_strequ(path, "./") || ft_strequ(path, "/"))
		new_train->file.path = ft_strmjoin(2, path, file);
	else
		new_train->file.path = (path) ? ft_strmjoin(3, path, "/", file) : NULL;
	if (tmp)
		ft_strdel(&tmp);
	if (ft_filename_check(&new_train))
		return (NULL);
	error = (path) ? lstat(new_train->file.path, &(new_train->file.stat)) :
		lstat(new_train->file.filename, &(new_train->file.stat));
	if (ft_checkerror(error, &new_train, file))
		return (NULL);
	new_train->file.isfile = !S_ISDIR(new_train->file.stat.st_mode);
	new_train->next = NULL;
	return (new_train);
}

t_train		*ft_trainfiles(t_train **root, int8_t mode, t_train **buf)
{
	t_train		*result;
	t_train		*temp;

	MAKE_NULL2(result, temp);
	while ((temp = ft_train_pop(root)))
	{
		temp->next = NULL;
		if ((mode == FILES && temp->file.isfile) ||
				(mode == DIRS && !temp->file.isfile))
			ft_lstrain_add(&result, temp);
		else if (mode == BOTH)
			ft_lstrain_add((temp->file.isfile) ? &result : buf, temp);
		else
			ft_memdel((void **)&temp);
	}
	return (result);
}

void		ft_trainfree(t_train **train)
{
	t_train		*ptr;

	ptr = *train;
	ft_strdel(&(ptr->file.link_path));
	ft_strdel(&(ptr->file.filename));
	ft_strdel(&(ptr->file.path));
	ft_memdel((void **)&ptr);
	*train = NULL;
}
