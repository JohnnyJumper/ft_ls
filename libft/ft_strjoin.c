/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtahirov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 02:26:29 by jtahirov          #+#    #+#             */
/*   Updated: 2018/03/13 00:25:07 by jtahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_length;
	int		s2_length;
	char	*new;

	if (!s1 || !s2)
		return ((s2) ? (char *)s2 : (char *)s1);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new = ft_strnew(s1_length + s2_length);
	if (!new)
		return (NULL);
	while (*s1 || *s2)
		*new++ = (*s1) ? *s1++ : *s2++;
	*new = '\0';
	return (new - s1_length - s2_length);
}
