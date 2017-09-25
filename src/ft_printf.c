/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 16:40:34 by elopez            #+#    #+#             */
/*   Updated: 2017/09/25 13:17:48 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_analyze(va_list ap, const char *fmt)
{
	int		ret;
	t_flags	flag;
	t_outp	op;

	ret = 0;
	op.str = ft_strcsub(fmt, '%');
//	if (*op.str == '\0')
//		ft_putendl("op.str0 == '\\0'");
	op.wlen = 0;
	while ((fmt = ft_strchr(fmt, '%')))
	{
		flag = pf_conv_flags(&fmt);// OK
		pf_conv_width(&fmt, &flag, ap);//OK
		pf_conv_precision(&fmt, &flag, ap);//OK
		pf_conv_length(&fmt, &flag);//OK
	//	if (!*op.str)
	//		ft_putendl("!op.str1");
		if ((pf_conv_spec(&fmt, &flag, &op, ap)) == -2)
			break ;
	//	if (!*op.str)
	//		ft_putendl("!op.str2");
		if (op.wlen > 0)
			ret += op.wlen;
		if (!*(++fmt))
			break ;
	//	if (!*op.str)
	//		ft_putendl("!op.str4");
		op.str = ft_strmer(op.str, ft_strcsub(fmt, '%'));
	//	if (!*op.str)
	//		ft_putendl("!op.str5");
	}
	if (!*op.str)
	{
//		ft_putendl("!op.str6");
		return (ret);
	}
//	ft_putnbr(ft_strlen(op.str));
	ret += write(1, op.str, ft_strlen(op.str));
	ft_strdel(&(op.str));
	return (ret);
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
