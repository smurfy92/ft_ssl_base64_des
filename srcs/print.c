/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 09:54:09 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/22 12:31:59 by jtranchi         ###   ########.fr       */
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
			ft_putstr(ft_itoa_base((int)p[y], 16));
	}
}

void	print_output_sha256(t_mem *mem)
{
	unsigned int *p;
	int		i;
	int		y;

	i = -1;
	while (++i < 8)
	{
		y = -1;
		p = (unsigned int *)&mem->h[i];
		ft_putstr(ft_itoa_base((uintmax_t)mem->h[i], 16));
		//while (++y < 4)
		//	ft_putstr(ft_itoa_base((unsigned int)p[y], 16));
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
