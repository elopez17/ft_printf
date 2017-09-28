/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 12:48:16 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/28 16:08:01 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_convspec g_convspec[] =
{//-1
	{'%', &pf_percent},
	{'C', &pf_wint_t},//1
	{'D', &pf_spec_di},
	{'F', &pf_spec_f},
	{'O', &pf_spec_o},//4
	{'S', &pf_wchar_t},
	{'U', &pf_spec_u},//6
	{'X', &pf_spec_xup},
	{'b', &pf_itobi},
	{'c', &pf_char},//9
	{'d', &pf_spec_di},
	{'f', &pf_spec_f},//11
	{'i', &pf_spec_di},
	{'k', &pf_iso8601},
	{'o', &pf_spec_o},//14
	{'p', &pf_spec_p},
	{'s', &pf_str},//16
	{'u', &pf_spec_u},
	{'x', &pf_spec_x}
};

static int	pf_invalid_spec(t_flags *flag, t_outp *op, char c)
{
	int len;

	if (flag->width > 1)
	{
		len = flag->width - 1;
		if (flag->zero)
			op->str = ft_strmer(op->str, MAKES('0', len));
		else if (!flag->left_adj)
			op->str = ft_strmer(op->str, MAKES(' ', len));
		op->str = ft_strmer(op->str, ft_strsub(&c, 0, (!c ? 0 : 1)));
		if (flag->left_adj)
			op->str = ft_strmer(op->str, MAKES(' ', len));
		return (0);
	}
	if (!c)
		return (-2);
	op->str = ft_strmer(op->str, ft_strsub(&c, 0, 1));
	return (0);
}

int			pf_conv_spec(const char **fmt, t_flags *flag, t_outp *op, va_list *ap)
{
	int i;

	op->wlen = 0;
	flag->l = (**fmt == 'D' || **fmt == 'U' || **fmt == 'O') ? 1 : flag->l;
	flag->alter = (**fmt == 'p') ? 1 : flag->alter;
	i = (**fmt > 'c' ? (**fmt > 'o' ? (**fmt > 's' ? 16 : 14) :\
(**fmt > 'f' ? 11 : 9)) : (**fmt > 'O' ? (**fmt > 'U' ? 6 : 4) :(**fmt > 'C' ? 1 : -1)));
	while (++i < TOTAL_SPECS)
	{
		if (**fmt == g_convspec[i].c)
		{
			g_convspec[i].f(flag, op, ap);
			return (0);
		}
	}
	if (**fmt == '{' && *(*fmt + 3) == '}')
		if (pf_color(fmt, op) == 0)
			return (0);
	return (pf_invalid_spec(flag, op, **fmt));
}
