/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 09:54:09 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/28 17:33:57 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_output_md5(t_mem *mem, t_opt *opt)
{
	uint8_t			*p;
	int				i;
	int				y;
	char			*tmp;

	i = -1;
	(!opt->stdin && !opt->r && !opt->q) ? (write_prefix(opt, opt->arg)) : 0;
	while (++i < 4)
	{
		y = -1;
		p = (uint8_t *)&mem->h[i];
		while (++y < 4)
		{
			tmp = ft_itoa_base((int)p[y], 16);
			if (ft_strlen(tmp) == 1)
				ft_putchar('0');
			ft_putstr(tmp);
			ft_strdel(&tmp);
		}
	}
	(!opt->stdin && opt->r && !opt->q) ? (write_suffix(opt->arg)) : 0;
	ft_putchar('\n');
}

void	print_output_sha256(t_mem *mem, t_opt *opt)
{
	unsigned int	*p;
	int				i;
	int				y;
	char			*tmp;

	(!opt->stdin && !opt->r && !opt->q) ? (write_prefix(opt, opt->arg)) : 0;
	i = -1;
	while (++i < 8)
	{
		p = (unsigned int *)&mem->h[i];
		tmp = ft_itoa_base((uintmax_t)mem->h[i], 16);
		y = ft_strlen(tmp);
		while (y++ < 8)
			ft_putchar('0');
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	(!opt->stdin && opt->r && !opt->q) ? (write_suffix(opt->arg)) : 0;
	ft_putchar('\n');
}

void	write_file_error(char *file, t_opt *opt)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(HASH[opt->hash]);
	ft_putstr(": ");
	ft_putstr(file);
	ft_putendl(": No such file or directory");
}

void	write_prefix(t_opt *opt, t_arg *arg)
{
	if (ft_strequ(HASH[opt->hash], "md5") == 1)
		ft_putstr("MD5 (");
	if (ft_strequ(HASH[opt->hash], "sha256") == 1)
		ft_putstr("SHA256 (");
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(arg->str);
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(") = ");
}

void	write_suffix(t_arg *arg)
{
	ft_putchar(' ');
	(arg->is_string) ? (ft_putchar('"')) : 0;
	ft_putstr(arg->str);
	(arg->is_string) ? (ft_putchar('"')) : 0;
}
