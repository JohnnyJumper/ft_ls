/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnfjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:40:17 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/10 17:14:03 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnfjoin(char **s1, char const *s2, int size)
{
	int		s1_length;
	int		s2_length;
	char	*new;
	int		min;

	if (!*s1 || !s2)
		return ((s2) ? ft_strdup(s2) : *s1);
	s1_length = ft_strlen(*s1);
	s2_length = ft_strlen(s2);
	min = MIN(s2_length, size);
	new = ft_strnew(s1_length + min);
	if (!new)
		return (NULL);
	while (*s1)
		*new++ = *(*s1)++;
	while (*s2 && size--)
		*new++ = *s2++;
	*new = '\0';
	ft_memdel((void **)s1);
	return (new - s1_length - min);
}
