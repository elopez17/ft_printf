/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 12:48:16 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/28 14:20:09 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_convspec g_convspec[] =
{
	{'%', &pf_percent},//0
	{'D', &pf_spec_di},
	{'C', &pf_wint_t},
	{'F', &pf_spec_f},//3
	{'U', &pf_spec_u},
	{'X', &pf_spec_xup},
	{'S', &pf_wchar_t},
	{'O', &pf_spec_o},//7
	{'d', &pf_spec_di},
	{'c', &pf_char},
	{'i', &pf_spec_di},
	{'o', &pf_spec_o},
	{'f', &pf_spec_f},//12
	{'s', &pf_str},
	{'u', &pf_spec_u},
	{'x', &pf_spec_x},
	{'p', &pf_spec_p},
	{'b', &pf_itobi},
	{'k', &pf_iso8601}
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

	i = -1;
	op->wlen = 0;
	flag->l = (**fmt == 'D' || **fmt == 'U' || **fmt == 'O') ? 1 : flag->l;
	flag->alter = (**fmt == 'p') ? 1 : flag->alter;
	i = **fmt >= 'a' ? (**fmt >= 'p' ? 12 : 7) : (**fmt >= 'O' ? 3 : -1);
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
