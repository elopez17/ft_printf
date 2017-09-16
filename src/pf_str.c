/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:33:29 by elopez            #+#    #+#             */
/*   Updated: 2017/09/14 20:35:33 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_width(t_flags *flag, char *s, int slen)
{
	int print;

	print = flag->width - slen;
	if (flag->zero)
		while (print--)
			write(1, "0", 1);
	else if (!flag->left_adj)
		while (print--)
			write(1, " ", 1);
	write(1, s, slen);
	if (flag->left_adj)
		while (print--)
			write(1, " ", 1);
}

int			pf_str(t_flags *flag, va_list ap)
{
	char	*s;
	int		len;

	if (flag->prec_num < 0)
		flag->prec = 0;
	if (flag->l)
		return (pf_wchar_t(flag, ap));
	if (!(s = va_arg(ap, char*)))
		s = ft_strdup("(null)");
	else
		s = ft_strdup(s);
	len = ft_strlen(s);
	if (flag->prec && flag->prec_num < len)
		len = flag->prec_num;
	if (flag->width > len)
	{
		print_width(flag, s, len);
		ft_strdel(&s);
		return (flag->width);
	}
	write(1, s, len);
	ft_strdel(&s);
	return (len);
}
