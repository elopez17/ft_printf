/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:33:29 by elopez            #+#    #+#             */
/*   Updated: 2017/09/21 15:52:04 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	len_arg(t_flags *flag, va_list ap)
{
	if (flag->l)
		return (va_arg(ap, long));
	if (flag->hh)
		return ((signed char)va_arg(ap, int));
	if (flag->h)
		return ((short)va_arg(ap, int));
	if (flag->ll)
		return (va_arg(ap, long long));
	if (flag->j)
		return (va_arg(ap, intmax_t));
	if (flag->z)
		return (va_arg(ap, ssize_t));
	return (va_arg(ap, int));
}

static void		print_width(t_flags *flag, t_outp *op, char **s, int *slen)
{
	char	*new_s;
	int		i;
	int		j;
	int		sign;

	i = 0;
	j = 0;
	new_s = ft_strnew(flag->width);
	if ((sign = ((*s)[j] != '+' && (*s)[j] != ' ' && (*s)[j] != '-') ? 0 : 1))
		new_s[i++] = (*s)[j++];
	while ((flag->prec && *slen - sign < flag->prec_num) ||\
			(flag->zero && *slen < flag->width))
	{
		new_s[i++] = '0';
		++(*slen);
	}
	while ((*s)[j] != '\0')
		new_s[i++] = (*s)[j++];
	if (flag->left_adj)
		op->str = ft_strmer(op->str, new_s);
	if (*slen < flag->width)
		op->str = ft_strmer(op->str, MAKES(' ', flag->width - *slen));
	if (!flag->left_adj)
		op->str = ft_strmer(op->str, new_s);
	ft_strdel(s);
}

static void		print_prec(t_flags *flag, t_outp *op, char **s, int *slen)
{
	int sign;

	if ((sign = (ft_isdigit(**s)) ? 0 : 1))
		op->str = ft_strmer(op->str, ft_strsub(*s, 0, 1));
	op->str = ft_strmer(op->str, MAKES('0', flag->prec_num - (*slen - sign)));
	op->str = ft_strmer(op->str, ft_strsub(*s, sign, *slen - sign));
	ft_strdel(s);
}

void			pf_spec_di(t_flags *flag, t_outp *op, va_list ap)
{
	intmax_t	val;
	char		*s;
	int			slen;

	flag->zero = (flag->prec == 1) ? 0 : flag->zero;
	val = len_arg(flag, ap);
	s = (!val && !HASLENGTH(flag) && (flag->prec && !flag->prec_num) &&\
			!HASFLAG(flag)) ? ft_strdup("") : ft_imttoa(val);
	if (val >= 0 && (flag->space || flag->sign))
		s = ft_strmer(ft_strdup((flag->space) ? " " : "+"), s);
	slen = ft_strlen(s);
	if (flag->width > slen && (flag->width > flag->prec_num || !flag->prec))
		print_width(flag, op, &s, &slen);
	else if (flag->prec && flag->prec_num > slen)
		print_prec(flag, op, &s, &slen);
	else
		op->str = ft_strmer(op->str, s);
}
