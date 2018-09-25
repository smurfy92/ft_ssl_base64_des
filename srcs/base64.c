/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 11:03:08 by jtranchi          #+#    #+#             */
/*   Updated: 2018/09/04 11:03:13 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	base64_encode(t_mem *mem, t_opt *opt)
{
	int i;
	int tmp;
	int len;

	i = 0;
	len = mem->len - (mem->len % 3);
	while (i < len)
	{
		tmp = 0;
		tmp = (mem->data[i] << 16) | (mem->data[i + 1] << 8) |
		(mem->data[i + 2]);
		print_base64_encode(opt, tmp, 0);
		i += 3;
	}
	tmp = 0;
	if (mem->len % 3 == 1)
	{
		tmp = mem->data[i] << 4;
		print_base64_encode(opt, tmp, 1);
	}
	if (mem->len % 3 == 2)
	{
		tmp = (mem->data[i] << 10) | (mem->data[i + 1] << 2);
		print_base64_encode(opt, tmp, 2);
	}
	ft_putchar_fd('\n', opt->fd);
}

void	clean_string(t_mem *mem)
{
	int i;

	i = 0;
	while (i < mem->len)
	{
		if (mem->data[i] == '=')
		{
			mem->len = i;
			mem->data[i] = 0;
			break ;
		}
		if (!ft_isalpha(mem->data[i]) && !ft_isdigit(mem->data[i]))
		{
			mem->data[i] = 0;
			if (i != mem->len - 1)
				mem->data = (unsigned char *)ft_strjoin_nf((char*)mem->data,
				(char*)&mem->data[i + 1], 1);
			mem->len--;
		}
		else
			i++;
	}
}

t_mem	*base64_decode(t_mem *mem)
{
	int		i;
	int		len;
	t_mem 	*tmp;

	tmp = NULL;
	i = 0;
	clean_string(mem);
	len = mem->len - (mem->len % 4);
	if (mem->data[mem->len - 1] == '=')
		len -= 4;
	while (i < len)
	{
		tmp = ft_memjoin(tmp, print_base64_decode(mem, i, 0));
		i += 4;
	}
	if (mem->len % 4 == 2)
		tmp = ft_memjoin(tmp, print_base64_decode(mem, i, 1));
	else if (mem->len % 4 == 3)
		tmp = ft_memjoin(tmp, print_base64_decode(mem, i, 2));
	return (tmp);
}

void	hash_base64(t_mem *mem, t_opt *opt)
{
	t_mem *ret;

	ret = NULL;
	if (!opt->d)
		base64_encode(mem, opt);
	else
	{
		ret = base64_decode(mem);
		write_fd(opt->fd, ret);
	}
}
