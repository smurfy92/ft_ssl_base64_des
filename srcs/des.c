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

int32_t g_des[56] = {
   57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4};

int32_t g_rev[64] = {
	40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

void	print_bits(char toto[8])
{
	int i = -1;
	int y;

	while (++i < 8)
	{
		y = -1;
		while (++y < 8)
		{
			if (toto[i] & (1 << (7-y)))
				ft_putchar('1');
			else
				ft_putchar('0');
		}
	}
}

void	final_permute(char toto[8])
{
	int i = -1;
	char tmp[8];

	bzero(tmp, 8);
	ft_putchar('\n');
	while (++i < 56)
	{
		if (toto[g_des[i] / 8] &  (1 << (7 - (g_des[i] % 8))))
			tmp[i / 8] |= 1 << (7 - i % 8);
	}
	print_bits(tmp);
}

void	initial_permute(char toto[8])
{
	int i = -1;
	char tmp[8];

	bzero(tmp, 8);
	// ft_putchar('\n');
	while (++i < 56)
	{
		if (toto[i / 8] &  (1 << (7 - (i % 8))))
			tmp[g_des[i] / 8] |= 1 << (7 - g_des[i] % 8);
	}
	// print_bits(tmp);
	final_permute(tmp);
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
	print_bits(cipher);
	initial_permute(cipher);

	opt = NULL;
	mem = padding_des(mem);
}