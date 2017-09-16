/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:04:21 by elopez            #+#    #+#             */
/*   Updated: 2017/08/01 13:04:24 by elopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_str_len(unsigned long long n)
{
	size_t		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_ulltoa(unsigned long long n)
{
	char				*str;
	size_t				str_len;
	unsigned long long	n_cpy;

	str_len = get_str_len(n);
	n_cpy = n;
	if (!(str = ft_strnew(str_len)))
		return (NULL);
	str[--str_len] = n_cpy % 10 + '0';
	while (n_cpy /= 10)
		str[--str_len] = n_cpy % 10 + '0';
	return (str);
}
