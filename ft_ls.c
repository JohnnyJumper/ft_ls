/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:17:39 by jtahirov          #+#    #+#             */
/*   Updated: 2018/02/19 00:46:43 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"
#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_lsmain		main;
	t_train			*args;
	int				parse_result;

	ft_bzero(&main, sizeof(t_lsmain));
	parse_result = ft_lsparse_flags(&main, argc, argv);
	argv += (parse_result) ? parse_result : 1;
	argc -= (parse_result) ? parse_result : 1;
	args = ft_lsget_args(&main, argc, argv);
	ft_lshandle_args(&args, &main);
	return (0);
}
