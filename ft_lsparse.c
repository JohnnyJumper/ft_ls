/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsparse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 00:00:10 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 01:32:00 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/ft_ls.h"

void			ft_lsusage(void)
{
	ft_printf("%s\n", LS_USAGE);
	exit(3);
}

static void		ft_lsparse_flags_helper(t_lsmain *main, char ch)
{
	if (ch == 'l')
		main->flag.l = true;
	else if (ch == 'R')
		main->flag.recur = true;
	else if (ch == 'a')
		main->flag.a = true;
	else if (ch == 'r')
		main->flag.r = true;
	else if (ch == 't')
		main->flag.t = true;
	else if (ch == 'S')
		main->flag.size = true;
	else if (ch == 'f')
	{
		main->flag.f = true;
		main->flag.a = true;
	}
	else if (ch == 'o')
		main->flag.o = true;
	else if (ch == 'p')
		main->flag.p = true;
	else if (ch == '?')
		ft_lsusage();
}

int				ft_lsparse_flags(t_lsmain *main, int argc, char **argv)
{
	char	ch;

	if (argc == 1)
		return (0);
	while ((ch = ft_getopt(argc, argv, ":lRartSfop")) != -1)
	{
		if (ch == ':')
			return (g_optind - 1);
		ft_lsparse_flags_helper(main, ch);
	}
	return (g_optind);
}
