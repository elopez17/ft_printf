/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:40:34 by elopez            #+#    #+#             */
/*   Updated: 2017/09/07 14:00:52 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_analyze(va_list ap, const char *fmt)
{
	int		len;
	int		ret;
	t_flags	flag;

	ret = 0;
	len = ft_putcstr(fmt, '%');
	while ((fmt = ft_strchr(fmt, '%')))
	{
		flag = pf_conv_flags(&fmt);// OK
		pf_conv_width(&fmt, &flag, ap);//OK
		pf_conv_precision(&fmt, &flag, ap);//OK
		pf_conv_length(&fmt, &flag);//OK
		if ((ret = pf_conv_specifier(&fmt, &flag, ap)) == -2)
			--fmt;
		else
			len += ret;
		len += ft_putcstr(++fmt, '%');
		len = (ret == -1) ? -1 : len;
	}
	return (len);
}

int			ft_printf(const char *fmt, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	if (fmt)
	{
		va_start(ap, fmt);
		len = pf_analyze(ap, fmt);
		va_end(ap);
	}
	return (len);
}
