/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsget_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 00:47:18 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:33:29 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

t_train			*ft_lsget_args(t_lsmain *main, int argc, char **argv)
{
	t_train		*root;
	int			counter;

	counter = 0;
	root = NULL;
	if (argc >= 2)
		main->multiple_arg = true;
	if (!main->flag.f)
		main->flag.lex = true;
	if (argc == 0)
		ft_lstrain_add(&root, ft_lstrain_create("./", NULL));
	while (argc--)
		ft_lstrain_add(&root, ft_lstrain_create(argv[counter++], NULL));
	return (root);
}

int				ft_lsget_total(t_train *current)
{
	int			total;

	total = 0;
	while (current)
	{
		total += current->file.stat.st_blocks;
		current = current->next;
	}
	return (total);
}

static void		ft_lsget_max_init(t_lsmain *main, t_train **curent,
												t_train **args)
{
	main->max_digit_link = -1;
	main->max_digit_size = -1;
	main->max_groupname_len = -1;
	main->max_ownername_len = -1;
	main->max_major = -1;
	main->max_minor = -1;
	*curent = *args;
}

void			ft_lsget_max(t_lsmain *main, t_train *args)
{
	t_train		*current;
	int			temp;

	ft_lsget_max_init(main, &current, &args);
	while (current && (temp = ft_countdig(current->file.stat.st_nlink)))
	{
		if (temp > main->max_digit_link)
			main->max_digit_link = temp;
		temp = ft_countdig(current->file.stat.st_size);
		if (temp > main->max_digit_size)
			main->max_digit_size = temp;
		temp = ft_strlen(ft_lsget_groupname(&current->file.stat));
		if (temp > main->max_groupname_len)
			main->max_groupname_len = temp;
		temp = ft_strlen(ft_lsget_ownername(&current->file.stat));
		if (temp > main->max_ownername_len)
			main->max_ownername_len = temp;
		temp = ft_countdig(major(current->file.stat.st_rdev));
		if (temp > main->max_major)
			main->max_major = temp;
		temp = ft_countdig(minor(current->file.stat.st_rdev));
		if (temp > main->max_minor)
			main->max_minor = temp;
		current = current->next;
	}
}

char			*ft_lsget_time(struct stat	*stat)
{
	char	*full_time;
	char	*result;
	time_t	today;

	result = ft_strnew(12);
	time(&today);
	full_time = ctime(&stat->st_mtimespec.tv_sec);
	if (ABS(stat->st_mtimespec.tv_sec - today) > 15770000)
	{
		ft_strncpy(result, full_time + 4, 7);
		ft_strncpy(result + 7, full_time + 19, 5);
	}
	else
		ft_strncpy(result, full_time + 4, 12);
	return (result);
}
