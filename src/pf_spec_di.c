/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:33:29 by elopez            #+#    #+#             */
/*   Updated: 2017/09/14 20:10:12 by eLopez           ###   ########.fr       */
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

static void		print_width(t_flags *flag, char *s, int *ret)
{
	char	*new_s;
	int		i;
	int		j;
	int		sign;

	i = 0;
	j = 0;
	new_s = ft_strnew(flag->width);
	if ((sign = (s[j] != '+' && s[j] != ' ' && s[j] != '-') ? 0 : 1))
		new_s[i++] = s[j++];
	while ((flag->prec && *ret - sign < flag->prec_num) ||\
			(flag->zero && *ret < flag->width))
	{
		new_s[i++] = '0';
		++(*ret);
	}
	while (s[j] != '\0')
		new_s[i++] = s[j++];
	if (flag->left_adj)
		write(1, new_s, i);
	while (*ret < flag->width && ++(*ret))
		write(1, " ", 1);
	if (!flag->left_adj)
		write(1, new_s, i);
	ft_strdel(&new_s);
}

static void		print_prec(t_flags *flag, char *s, int *ret)
{
	int sign;

	if ((sign = (ft_isdigit(*s)) ? 0 : 1))
		ft_putchar(*s++);
	while ((*ret) - sign < flag->prec_num)
	{
		++(*ret);
		write(1, "0", 1);
	}
	ft_putstr(s);
}

int				pf_spec_di(t_flags *flag, va_list ap)
{
	intmax_t	val;
	char		*s;
	int			ret;

	flag->zero = (flag->prec == 1) ? 0 : flag->zero;
	val = len_arg(flag, ap);
	s = (!val && !HASLENGTH(flag) && (flag->prec && !flag->prec_num) && !HASFLAG(flag)) ?\
		ft_strdup("") : ft_imttoa(val);
	if (val >= 0 && (flag->space || flag->sign))
		s = ft_strmer(ft_strdup((flag->space) ? " " : "+"), s);
	ret = ft_strlen(s);
	if (flag->width > ret)
		print_width(flag, s, &ret);
	else if (flag->prec && flag->prec_num > ret)
		print_prec(flag, s, &ret);
	else
		write(1, s, ret);
	ft_strdel(&s);
	return (ret);
}
