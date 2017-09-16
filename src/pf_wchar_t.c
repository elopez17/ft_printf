/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wchar_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:39:32 by elopez            #+#    #+#             */
/*   Updated: 2017/09/08 21:36:50 by eLopez           ###   ########.fr       */
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

static void			print_width(t_flags *flag, wchar_t *s, int slen)
{
	int print;

	print = flag->width - slen;
	if (flag->zero)
		while (print--)
			write(1, "0", 1);
	else if (!flag->left_adj)
		while (print--)
			write(1, " ", 1);
	while (slen >= wintlen(*s) && *s)
		slen -= ft_putwint(*s++);
	if (flag->left_adj)
		while (print--)
			write(1, " ", 1);
}

int					pf_wchar_t(t_flags *flag, va_list ap)
{
	wchar_t	*s;
	int		len;

	if (!(s = va_arg(ap, wchar_t*)))
		return (write(1, "(null)", 6));
	len = ft_wcharlen(s);
	if (flag->prec && flag->prec_num < len)
	{
		len = flag->prec_num - (flag->prec_num % wintlen(*s));
		flag->prec_num = len;
	}
	if (flag->width > len)
	{
		print_width(flag, s, len);
		return (flag->width);
	}
	else if (flag->prec && flag->prec_num == len)
	{
		while (flag->prec_num && *s)
			flag->prec_num -= ft_putwint(*s++);
		return (len);
	}
	while (*s)
		ft_putwint(*s++);
	return (len);
}
