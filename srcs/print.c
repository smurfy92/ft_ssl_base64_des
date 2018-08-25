/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 09:54:09 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/25 16:28:13 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_output(t_mem *mem)
{
	uint8_t	*p;
	int		i;
	int		y;

	i = -1;
	while (++i < 4)
	{
		y = -1;
		p = (uint8_t *)&mem->h[i];
		while (++y < 4)
		{
			if (ft_strlen(ft_itoa_base((int)p[y], 16)) == 1)
				ft_putchar('0');
			ft_putstr(ft_itoa_base((int)p[y], 16));
		}
	}
}

void	print_output_sha256(t_mem *mem)
{
	unsigned int	*p;
	int				i;
	int				y;

	i = -1;
	while (++i < 8)
	{
		p = (unsigned int *)&mem->h[i];
		y = ft_strlen(ft_itoa_base((uintmax_t)mem->h[i], 16));
		while (y++ < 8)
			ft_putchar('0');
		ft_putstr(ft_itoa_base((uintmax_t)mem->h[i], 16));
	}
}

void	write_file_error(char *file, t_opt *opt)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(opt->hash);
	ft_putstr(": ");
	ft_putstr(file);
	ft_putendl(": No such file or directory");
}

void	write_prefix(t_opt *opt, t_arg *arg)
{
	if (ft_strequ(opt->hash, "md5") == 1)
		ft_putstr("MD5 (");
	if (ft_strequ(opt->hash, "sha256") == 1)
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
