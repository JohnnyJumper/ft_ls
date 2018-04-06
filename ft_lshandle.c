/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lshandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:26:06 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/14 20:46:20 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

static	t_train		*ft_lsdir_read(char *pathname, t_lsmain *main)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	t_train			*train;

	dir_stream = opendir(pathname);
	if (!dir_stream)
	{
		ft_printf("ft_ls: %s: Permission denied\n", pathname);
		return (NULL);
	}
	MAKE_NULL2(train, dir);
	while ((dir = readdir(dir_stream)) != NULL)
	{
		if ((!main->flag.a) && *dir->d_name == '.')
			continue ;
		ft_lstrain_add(&train, ft_lstrain_create(dir->d_name, pathname));
	}
	closedir(dir_stream);
	return (train);
}

static void			ft_lshandle_dirs_helper(t_lsmain *main, t_train **train)
{
	t_train		*dir;

	dir = NULL;
	if ((main->flag.l || main->flag.o) && *train)
		ft_printf("total %i\n", ft_lsget_total(*train));
	ft_lssort(&*train, main);
	ft_lsprint(*train, main);
	if (main->flag.recur)
	{
		dir = ft_trainfiles(&*train, DIRS, NULL);
		*train = NULL;
		ft_lssort(&dir, main);
		ft_lshandle_dirs(&dir, main, false);
	}
}

void				ft_lshandle_dirs(t_train **dirs, t_lsmain *main, bool first)
{
	t_train		*temp;
	t_train		*train;
	char		*path;

	if (!*dirs)
		return ;
	while ((temp = ft_train_pop(dirs)))
	{
		path = (temp->file.path) ? temp->file.path : temp->file.filename;
		if ((ft_strequ(temp->file.filename, ".") ||
					ft_strequ(temp->file.filename, "..")) && !first)
		{
			ft_memdel((void **)&temp);
			continue ;
		}
		if (!first)
			ft_printf("\n%s:\n", path);
		train = ft_lsdir_read(path, main);
		ft_lshandle_dirs_helper(main, &train);
		ft_memdel((void **)&temp);
	}
}

void				ft_lshandle_args(t_train **args, t_lsmain *main)
{
	t_train		*files;
	t_train		*dirs;
	bool		first;

	MAKE_NULL2(files, dirs);
	if (!*args)
		return ;
	first = true;
	if (!main->multiple_arg && (*args)->file.isfile)
	{
		ft_lsprint(*args, main);
		return ;
	}
	files = ft_trainfiles(args, BOTH, &dirs);
	args = NULL;
	ft_lssort(&files, main);
	ft_lssort(&dirs, main);
	if (files && !(first = false))
		ft_lsprint(files, main);
	if (dirs)
	{
		ft_lshandle_dirs(&dirs, main, first);
		ft_traindel(&dirs);
	}
}
