/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 12:48:16 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/20 12:39:09 by eLopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_convspec g_convspec[] =
{
	{'%', &pf_percent},
	{'d', &pf_spec_di},
	{'i', &pf_spec_di},
	{'D', &pf_spec_di},
	{'s', &pf_str},
	{'c', &pf_char},
	{'S', &pf_wchar_t},
	{'C', &pf_wint_t},
	{'p', &pf_spec_p},
	{'u', &pf_spec_u},
	{'U', &pf_spec_u},
	{'x', &pf_spec_x},
	{'X', &pf_spec_xup},
	{'o', &pf_spec_o},
	{'O', &pf_spec_o},
	{'f', &pf_spec_f},
	{'F', &pf_spec_f}
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

int			pf_conv_spec(const char **fmt, t_flags *flag, t_outp *op, va_list ap)
{
	int i;

	i = -1;
	op->wlen = 0;
	flag->l = (**fmt == 'D' || **fmt == 'U' || **fmt == 'O') ? 1 : flag->l;
	flag->alter = (**fmt == 'p') ? 1 : flag->alter;
	while (++i < TOTAL_SPECS)
	{
		if (**fmt == g_convspec[i].c)
		{
			g_convspec[i].f(flag, op, ap);
			return (0);
		}
	}
	return (pf_invalid_spec(flag, op, **fmt));
}
