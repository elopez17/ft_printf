/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:42:05 by elopez            #+#    #+#             */
/*   Updated: 2017/09/12 15:41:37 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PREC_VAL(f) (f->prec && f->prec_num > 0) ? f->prec_num : 0

static char	*itox(uintmax_t dec)
{
	char	tmp[12];
	char	*s;
	int		i;
	int		j;
	int		remain;

	i = -1;
	j = -1;
	while (dec)
	{
		remain = dec % 16;
		tmp[++i] = (remain < 10 ? 48 : 87) + remain;
		dec /= 16;
	}
	s = ft_strnew(i + 1);
	while (i >= 0)
	{
		s[++j] = tmp[i--];
	}
	return (s);
}

static void	print_prec(t_flags *flag, char *s, int *ret)
{
	flag->prec_num -= (*ret - 2);
	write(1, s, 2);
	while (flag->prec_num--)
		*ret += write(1, "0", 1);
	ft_putstr(s + 2);
}

static void	print_width(t_flags *flag, char *s, int *ret)
{
	flag->prec_num -= *ret - 2;
	flag->width = (flag->width - *ret) - (PREC_VAL(flag));
	*ret += flag->width + (PREC_VAL(flag));
	if (flag->left_adj)
	{
		write(1, s, 2);
		if (flag->prec)
			while (flag->prec_num-- > 0)
				write(1, "0", 1);
		ft_putstr(s + 2);
		while (flag->width--)
			write(1, " ", 1);
		return ;
	}
	if (flag->zero && write(1, s, 2))
		while (flag->width--)
			write(1, "0", 1);
	else
		while (flag->width-- > 0)
			write(1, " ", 1);
	(!flag->zero) ? write(1, s, 2) : 0;
	while (flag->prec_num-- > 0)
		write(1, "0", 1);
	ft_putstr(s + 2);
}

int			pf_spec_p(t_flags *flag, va_list ap)
{
	uintmax_t	dec;
	int			len;
	char		*s;

	if (!(dec = va_arg(ap, uintmax_t)))
		s = ft_strdup((flag->prec && !flag->prec_num ? "0x" : "0x0"));
	else
		s = ft_strmerge(ft_strdup("0x"), itox(dec));
	len = ft_strlen(s);
	if (flag->width > len && (!flag->prec || flag->width > flag->prec_num))
		print_width(flag, s, &len);
	else if (flag->prec && flag->prec_num > len - 2)
		print_prec(flag, s, &len);
	else
		ft_putstr(s);
	ft_strdel(&s);
	return (len);
}
