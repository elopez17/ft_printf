/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:33:29 by elopez            #+#    #+#             */
/*   Updated: 2017/09/08 21:48:55 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_percent(t_flags *flag, va_list ap)
{
	int	len;

	if (flag->width > 1 && ap)
	{
		len = flag->width - 1;
		if (flag->zero)
			while (len--)
				write(1, "0", 1);
		else if (!flag->left_adj)
			while (len--)
				write(1, " ", 1);
		write(1, "%", 1);
		if (flag->left_adj)
			while (len--)
				write(1, " ", 1);
		return (flag->width);
	}
	return (write(1, "%", 1));
}
