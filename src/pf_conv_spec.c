/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eLopez <elopez@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 12:48:16 by eLopez            #+#    #+#             */
/*   Updated: 2017/09/14 18:33:23 by eLopez           ###   ########.fr       */
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

static int	pf_invalid_spec(t_flags *flag, char c)
{
	int print;

	if (flag->width > 1)
	{
		print = flag->width - 1;
		if (flag->zero)
			while (print--)
				write(1, "0", 1);
		else if (!flag->left_adj)
			while (print--)
				write(1, " ", 1);
		c ? write(1, &c, 1) : 0;
		if (flag->left_adj)
			while (print--)
				write(1, " ", 1);
		return (flag->width);
	}
	if (!c)
		return (-2);
	return (write(1, &c, 1));
}

int			pf_conv_specifier(const char **fmt, t_flags *flag, va_list ap)
{
	int i;

	i = -1;
	flag->l = (**fmt == 'D' || **fmt == 'U' || **fmt == 'O') ? 1 : flag->l;
	flag->alter = (**fmt == 'p') ? 1 : flag->alter;
	while (++i < TOTAL_SPECS)
	{
		if (**fmt == g_convspec[i].c)
			return (g_convspec[i].f(flag, ap));
	}
	return (pf_invalid_spec(flag, **fmt));
}
