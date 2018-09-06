/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 13:31:16 by jtranchi          #+#    #+#             */
/*   Updated: 2018/09/06 13:31:16 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int32_t g_des[64] = {
   57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4};

void	print_bits(char toto[8], char titi[8])
{
	int i = -1;
	int y;
	int temp;

	while (++i < 8)
	{
		y = -1;
		while (++y < 8)
		{
			ft_putstr("i -> ");
			temp = (i * 8)+y;
			ft_putnbr(temp);
			ft_putstr(" -> ");
			if (toto[i] & (1 << (7-y)))
				ft_putchar('1');
			else
				ft_putchar('0');
			ft_putchar(' ');
			if (titi[i] & (1 << (7-y)))
				ft_putchar('1');
			else
				ft_putchar('0');
			ft_putchar('\n');
		}
	}
}

void	initial_permute(char toto[8])
{
	int i = -1;
	char tmp[8];

	ft_putchar('\n');
	while (++i < 56)
	{
		if (toto[i / 8] &  (1 << (7 - (i % 8))))
			tmp[g_des[i] / 8] |= 1 << (7 - g_des[i] % 8);
		else
			tmp[g_des[i] / 8] |= 0 << (7 - g_des[i] % 8);
	}
	print_bits(tmp, toto);
}

t_mem	*padding_des(t_mem *mem)
{
	int		len;
	t_mem	*message;

	len = mem->len;
	while (len % 8 != 0)
		len++;
	message = (t_mem *)malloc(sizeof(t_mem));
	message->data = (unsigned char *)ft_strnew(len);
	ft_memcpy(message->data, mem->data, mem->len);
	message->len = len;
	while (++mem->len <= len)
		message->data[mem->len] = 0;
	ft_free_mem(mem);
	return (message);
}

void	hash_des(t_mem *mem, t_opt *opt)
{
	char cipher[8] = "abcdefgh";
	initial_permute(cipher);
	opt = NULL;
	mem = padding_des(mem);
}