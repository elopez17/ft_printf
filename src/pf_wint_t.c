/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wint_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 00:04:22 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/08 21:46:50 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline int	wintlen(wint_t wi)
{
	if (wi <= (MB_CUR_MAX == 1 ? 0xff : 0x7f))
		return (1);
	else if (wi <= 0x7ff)
		return (2);
	else if (wi <= 0xffff)
		return (3);
	else
		return (4);
}

static inline int	print_width(wint_t cval, t_flags *flag, int len)
{
	int printed;

	printed = 0;
	if (flag->zero)
		while (len--)
			printed += write(1, "0", 1);
	else if (!flag->left_adj)
		while (len--)
			printed += write(1, " ", 1);
	printed += ft_putwint(cval);
	if (flag->left_adj)
		while (len--)
			printed += write(1, " ", 1);
	return (printed);
}

int					pf_wint_t(t_flags *flag, va_list ap)
{
	wint_t c;

	c = va_arg(ap, wint_t);
	if (flag->width > wintlen(c))
	{
		return (print_width(c, flag, flag->width - wintlen(c)));
	}
	return (ft_putwint(c));
}
