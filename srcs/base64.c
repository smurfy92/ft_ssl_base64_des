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

char g_base64[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5',
'6', '7', '8', '9', '+', '/'};

void    print_bits(unsigned char octet)
{
    int z = 128, oct = octet;

    while (z > 0)
    {
        if (oct & z)
            write(1, "1", 1);
        else
            write(1, "0", 1);
        z >>= 1;
    }
    ft_putchar('\n');
}

void	print_output_base64(t_mem *mem)
{
	mem = NULL;
}

t_mem	*padding_base64(t_mem *mem)
{
	return (mem);
}

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
		tmp = (mem->data[i] << 16) | (mem->data[i + 1] << 8) | (mem->data[i + 2]);
		ft_putchar_fd(g_base64[(tmp >> 18) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[(tmp >> 12) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[(tmp >> 6) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[tmp & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		i += 3;
	}
	if (mem->len % 3 == 1)
	{
		tmp = 0;
		tmp = mem->data[i] << 4;
		ft_putchar_fd(g_base64[(tmp >> 6) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[tmp & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd('=', (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd('=', (opt->fd > 1) ? opt->fd : 1);
	}
	if (mem->len % 3 == 2)
	{
		tmp = 0;
		tmp = (mem->data[i] << 10) | (mem->data[i + 1] << 2);
		ft_putchar_fd(g_base64[(tmp >> 12) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[(tmp >> 6) & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd(g_base64[tmp & 0x3F], (opt->fd > 1) ? opt->fd : 1);
		ft_putchar_fd('=', (opt->fd > 1) ? opt->fd : 1);
	}
}

int		get_value(char c)
{
	int i;

	i = -1;
	while (++i < 64)
	{
		if (g_base64[i] == c)
			return (i);
	}
	return (-1);
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
			if (i != mem->len - 1)
			{
				mem->data[i] = 0;
				mem->data = (unsigned char *)ft_strjoin_nf((char*)mem->data, (char*)&mem->data[i + 1], 1);
			}
			else
				mem->data[i] = 0;
			mem->len--;
		}
		else
			i++;
	}
}

void	base64_decode(t_mem *mem, t_opt *opt)
{
	int i;
	int len;
	char *tmp;

	i = 0;
	clean_string(mem);
	len = mem->len - (mem->len % 4);
	if (mem->data[mem->len - 1] == '=')
		len -= 4;
	while (i < len)
	{
		tmp = ft_strnew(3);
		tmp[0] = (get_value(mem->data[i]) << 2) | (get_value(mem->data[i + 1]) >> 4);
		tmp[1] = (get_value(mem->data[i + 1]) << 4) | (get_value(mem->data[i + 2]) >> 2);
		tmp[2] = (get_value(mem->data[i + 2]) << 6) | (get_value(mem->data[i + 3]));
		ft_putstr_fd(tmp, (opt->fd > 1) ? opt->fd : 1);
		i += 4;
	}
	if (mem->len % 4 == 2)
	{
		tmp = ft_strnew(3);
		tmp[0] = (get_value(mem->data[i]) << 2) | (get_value(mem->data[i + 1]) >> 4);
		tmp[1] = (get_value(mem->data[i + 1]) & 0xF);
		ft_putstr_fd(tmp, (opt->fd > 1) ? opt->fd : 1);
	}
	else if (mem->len % 4 == 3)
	{
		tmp = ft_strnew(3);
		tmp[0] = (get_value(mem->data[i]) << 2) | (get_value(mem->data[i + 1]) >> 4);
		tmp[1] = (get_value(mem->data[i + 1]) << 4) | (get_value(mem->data[i + 2]) >> 2);
		tmp[2] = (get_value(mem->data[i + 2]) << 6);
		ft_putstr_fd(tmp, (opt->fd > 1) ? opt->fd : 1);
	}
}

void	hash_base64(t_mem *mem, t_opt *opt)
{
	if (!opt->d)
	 	base64_encode(mem, opt);
	else
		base64_decode(mem, opt);
}