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

int32_t g_des_initial[64] = {
	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

int32_t g_des_final[64] = {
	40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

int32_t	g_des_expansion[56] = {
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

void	print_bits(char *toto, int length)
{
	int i = -1;
	int y;

	while (++i < length)
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
	ft_putchar('\n');
}

void	final_permute(char toto[8])
{
	int i = -1;
	char tmp[8];

	bzero(tmp, 8);
	ft_putchar('\n');
	while (++i < 64)
	{
		if (toto[(g_des_final[i] - 1) / 8] &  (1 << (7 - ((g_des_final[i] - 1) % 8))))
			tmp[i / 8] |= 1 << (7 - i % 8);
	}
}

char	*permute(char *to_permute, int32_t *tab, int length)
{
	int i = -1;
	char *tmp;

	tmp = ft_strnew(8);
	bzero(tmp, 8);
	while (++i < length)
		(to_permute[(tab[i] - 1) / 8] &  (1 << (7 - ((tab[i] - 1) % 8)))) ?
		(tmp[i / 8] |= 1 << (7 - i % 8)) : 0;
	return (tmp);
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


// void	substitute(char  *text, int tour)
// {

// }

// void	substitution(char *48text)
// {
// 	int i;

// 	i = -1;
// 	while (++i < 8)
// 	{
// 		substitute(48text, i);
// 	}
// }

void	round_des(char *right)
{
	char *tmp;
	char	key[6] = "aaaaaa";

	tmp = malloc(sizeof(char) * 13);
	ft_bzero(tmp, 13);
	tmp = permute(right, g_des_expansion, 56);
	int y = -1;
	int e;
	while (++y < 6)
	{
		e = -1;
		while (++e < 8)
			tmp[y] ^= key[y] & (1 << (7 - e));
	}
	// substitution(tmp);
	print_bits(tmp, 12);
}

void	hash_des(t_mem *mem, t_opt *opt)
{
	char cipher[8] = "abcdefgh";
	char *left;
	char *right;
	char *ret;
	char *tmp;
	print_bits(cipher, 8);
	ret = permute(cipher, g_des_initial, 64);
	print_bits(ret, 8);
	left = (char*)malloc(sizeof(char) * 5);
	right = (char*)malloc(sizeof(char) * 5);
	tmp = (char*)malloc(sizeof(char) * 5);
	ft_bzero(left, 5);
	ft_bzero(right, 5);
	ft_memcpy(left, ret, 4);
	ft_memcpy(right, (ret + 4), 4);
	int i = -1;
	while (++i < 1)
	{
		bzero(tmp, 5);
		round_des(right);
		ft_memcpy(tmp, left, 4);
		ft_memcpy(left, right, 4);
		ft_memcpy(right, tmp, 4);
	}
	ret = permute(ret, g_des_final, 64);
	print_bits(ret, 8);
	opt = NULL;
	mem = padding_des(mem);
}