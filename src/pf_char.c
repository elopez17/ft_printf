/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:06:26 by elopez            #+#    #+#             */
/*   Updated: 2017/09/08 21:20:25 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pf_char(t_flags *flag, va_list ap)
{
	unsigned char	c;
	int				print;

	if (flag->l)
		return (pf_wint_t(flag, ap));
	c = va_arg(ap, int);
	if (flag->width > 1)
	{
		print = flag->width - 1;
		if (flag->zero)
			while (print--)
				write(1, "0", 1);
		else if (!flag->left_adj)
			while (print--)
				write(1, " ", 1);
		write(1, &c, 1);
		if (flag->left_adj)
			while (print--)
				write(1, " ", 1);
		return (flag->width);
	}
	return (write(1, &(c), 1));
}
