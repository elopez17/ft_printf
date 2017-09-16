/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:42:05 by elopez            #+#    #+#             */
/*   Updated: 2017/09/14 18:13:02 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	len_arg(t_flags *flag, va_list ap)
{
	if (flag->l)
		return (va_arg(ap, unsigned long));
	if (flag->hh)
		return ((unsigned char)va_arg(ap, unsigned int));
	if (flag->h)
		return ((unsigned short)va_arg(ap, unsigned int));
	if (flag->ll)
		return (va_arg(ap, unsigned long long));
	if (flag->j)
		return (va_arg(ap, uintmax_t));
	if (flag->z)
		return (va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}

static char			*itoo(uintmax_t dec)
{
	char	tmp[20];
	char	*s;
	int		i;
	int		j;
	int		remain;

	i = -1;
	j = -1;
	while (dec)
	{
		remain = dec % 8;
		tmp[++i] = 48 + remain;
		dec /= 8;
	}
	s = ft_strnew(i + 1);
	while (i >= 0)
	{
		s[++j] = tmp[i--];
	}
	return (s);
}

static char			*add_zeros(t_flags *flag, int *len)
{
	char	*str;
	int		zeros;

	zeros = 0;
	if (flag->prec && flag->prec_num > *len + flag->alter)
	{
		zeros = flag->prec_num - (*len + flag->alter);
		*len += zeros;
	}
	*len += (flag->alter ? 1 : 0);
	if (flag->zero)
	{
		flag->width -= *len;
		if (flag->width > zeros)
		{
			zeros = flag->width;
			*len += zeros;
		}
	}
	ft_memset((str = ft_strnew(zeros)), '0', zeros);
	flag->alter ? str = ft_strmer(ft_strdup("0"), str) : NULL;
	return (str);
}

static void			print_width(t_flags *flag, char *s, int *ret)
{
	flag->width -= *ret;
	*ret += flag->width;
	if (flag->left_adj)
	{
		ft_putstr(s);
		while (flag->width--)
			write(1, " ", 1);
		return ;
	}
	while (flag->width-- > 0)
		write(1, " ", 1);
	ft_putstr(s);
}

int					pf_spec_o(t_flags *flag, va_list ap)
{
	uintmax_t	dec;
	int			len;
	char		*s;

	if (!(dec = len_arg(flag, ap)))
		s = ft_strdup(((flag->prec && !flag->prec_num) || flag->alter ? "" : "0"));
	else
		s = itoo(dec);
	if ((len = ft_strlen(s)) || flag->alter)
		s = ft_strmer(add_zeros(flag, &len), s);
	if (flag->width > len)
		print_width(flag, s, &len);
	else
		ft_putstr(s);
	ft_strdel(&s);
	return (len);
}
