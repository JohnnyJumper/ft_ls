/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uttility.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 21:02:40 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:17:48 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"

static char		*ft_lsget_linkpath(t_file *file)
{
	ssize_t		len;

	file->link_path = ft_strnew(1024);
	if ((len = readlink((file->path) ? (file->path) : file->filename,
					file->link_path, 1023)) != -1)
		file->link_path[len] = '\0';
	return (file->link_path);
}

static void		ft_lsprint_help(t_train *input, t_lsmain *main)
{
	if (main->flag.l || main->flag.o)
	{
		ft_printf("%-11s ", ft_lsget_mode(&input->file));
		ft_printf("%*lli ", main->max_digit_link, input->file.stat.st_nlink);
		ft_printf("%-*s  ", main->max_ownername_len,
				ft_lsget_ownername(&input->file.stat));
		if (main->flag.l && !main->flag.o)
			ft_printf("%-*s  ", main->max_groupname_len,
					ft_lsget_groupname(&input->file.stat));
		if (S_ISCHR(input->file.stat.st_mode) ||
				S_ISBLK(input->file.stat.st_mode))
			ft_printf("%*lli, %*lli ", main->max_major,
					major(input->file.stat.st_rdev),
					main->max_minor, minor(input->file.stat.st_rdev));
		else
			ft_printf("%*lli ", main->max_digit_size, input->file.stat.st_size);
		ft_printf("%s ", ft_lsget_time(&input->file.stat));
	}
}

void			ft_lsprint(t_train *input, t_lsmain *main)
{
	ft_lsget_max(main, input);
	while (input)
	{
		ft_lsprint_help(input, main);
		ft_printf("%s", input->file.filename);
		if (main->flag.p && !input->file.isfile)
			ft_printf("/");
		if (S_ISLNK(input->file.stat.st_mode))
			ft_printf(" -> %s\n", ft_lsget_linkpath(&input->file));
		else
			ft_printf("\n");
		input = input->next;
	}
}

void			ft_printf_node(t_train *node)
{
	while (node != NULL)
	{
		ft_printf("\033[0;32m%s\033[0m -> ", node->file.filename);
		node = node->next;
	}
	ft_printf("NULL\n");
}
