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

int32_t g_des_pc1[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

int32_t g_des_pc2[56] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

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

int32_t g_des_sub[8][4][16] = {
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
};

int32_t g_des_permut[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
    2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

int32_t g_des_shift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

long g_subkeys[17][3];


void	print_bits(long toto, int length)
{
	int i = -1;

	while (++i < length)
	{
			if ((toto >> (length - 1 - i) & 0x1) & 0x1)
				ft_putchar('1');
			else
				ft_putchar('0');
	}
	ft_putchar('\n');
}

long	permute(long to_permute, int32_t *tab, int length)
{
	int i = -1;
	long tmp;
	long save;

	tmp = 0;

	while (++i < length)
	{
		save = 0;
		save |= ((to_permute >> (64 - tab[i])) & 0x1);
		tmp |= save << (63 - i);
	}
	tmp >>= 64 - length;
	if (length == 56)
		tmp &= 0xFFFFFFFFFFFFFF;
	if (length == 32)
		tmp &= 0xFFFFFFFF;
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


int32_t        ft_s_funct(char data, int32_t tab[4][16])
{
    int    row;
    int    col;

    row = 0;
    col = 0;
    row = (((data >> 4) & 0x2) | (data & 0x1));
    col = (data & 0x1E) >> 1;
    return (tab[row][col]);
}

long        ft_function_s(long xor)
{
    return (ft_s_funct((xor >> 42) & 0x3F, g_des_sub[0]) << 28 |
                ft_s_funct((xor >> 36) & 0x3F, g_des_sub[1]) << 24 |
                ft_s_funct((xor >> 30) & 0x3F, g_des_sub[2]) << 20 |
                ft_s_funct((xor >> 24) & 0x3F, g_des_sub[3]) << 16 |
                ft_s_funct((xor >> 18) & 0x3F, g_des_sub[4]) << 12 |
                ft_s_funct((xor >> 12) & 0x3F, g_des_sub[5]) << 8 |
                ft_s_funct((xor >> 6) & 0x3F, g_des_sub[6]) << 4 |
                ft_s_funct((xor >> 0) & 0x3F, g_des_sub[7]) << 0);
}

long        ft_msg_to_long(char *data, int len)
{
    long    save;
    long    tmp;
    int        i;
    // int        a;

    i = -1;
    tmp = 0;
    // a = 0;
    while (++i < 8)
    {
        save = 0;
        if (i < len)
            save = data[i] & 0xFF;
        else
        {
        	// if (a == 0)
        	// 	save = 0x0A;
        	// else
            	save = 0x00;
            // a++;
        }
        // if (save == 10 && i < len)
        // 	save = 0x0D;
        tmp |= (save & 0xFF) << (64 - (8 * (i + 1)));
    }
    printf("hex -> %lX\n", tmp);
    return (tmp);
}

long	generate_subkeys(long message, t_opt *opt)
{
	long ret;
	long key;
	int i;
	long left;
	long right;
	long save_right;

	key = (opt->key != 0) ? (opt->key) : 1383827165325090801;
	i = 0;
	right = 0;
	left = 0;
	save_right = 0;
	ret = permute(key, g_des_pc1, 56);
	g_subkeys[0][0] = ret >> 28;
	g_subkeys[0][1] = ret & 0xFFFFFFF;
	ret = permute(message, g_des_initial, 64);
	left = (ret >> 32) & 0xFFFFFFFF;
	right = ret & 0xFFFFFFFF;
	while (++i <= 16)
	{

		g_subkeys[i][0] = ((g_subkeys[i - 1][0] << g_des_shift[i - 1]) | (g_subkeys[i - 1][0] >> (28 - g_des_shift[i - 1]))) & 0xFFFFFFF;
		g_subkeys[i][1] = ((g_subkeys[i - 1][1] << g_des_shift[i - 1]) | (g_subkeys[i - 1][1] >> (28 - g_des_shift[i - 1]))) & 0xFFFFFFF;
		g_subkeys[i][2] = permute(((g_subkeys[i][0] << 28) | g_subkeys[i][1]) << 8, g_des_pc2, 56) >> 8;
		save_right = right;
		ret = permute(right << 32, g_des_expansion, 48);
		ret = g_subkeys[i][2] ^ ret;
		ret = ft_function_s(ret);
		ret = permute(ret << 32, g_des_permut, 32);
		right = left ^ ret;
		left = save_right;
	}
	ret = ((right << 32) & 0xFFFFFFFF00000000) | (left & 0xFFFFFFFF);
	ret = permute(ret , g_des_final, 64);
	return (ret);
}

void	hash_des(t_mem *mem, t_opt *opt)
{
	long ret;
	t_mem	*tmp;
	t_mem	*message;

	ret = 0;
	message = NULL;
	mem = padding_des(mem);
	while (mem->len > 0)
	{
		ret = generate_subkeys(ft_msg_to_long((char*)mem->data, mem->len), opt);
		if (opt->a)
		{
			tmp = (t_mem *)malloc(sizeof(t_mem));
			tmp->data = (unsigned char*)ft_strnew(8);
			tmp->data[0] = (ret >> 56) & 0xFF;
			tmp->data[1] = (ret >> 48) & 0xFF; 
			tmp->data[2] = (ret >> 40) & 0xFF; 
			tmp->data[3] = (ret >> 32) & 0xFF; 
			tmp->data[4] = (ret >> 24) & 0xFF; 
			tmp->data[5] = (ret >> 16) & 0xFF;
			tmp->data[6] = (ret >> 8) & 0xFF; 
			tmp->data[7] = ret & 0xFF;
			printf("mem->len%d\n", mem->len );
			tmp->len = 8;
			message = ft_memjoin(message, tmp);	
		}
		else
			printf("ret finale -> %lX\n", ret);
		mem->data += 8; 
		mem->len -= 8;
	}
	if (opt->a)
		hash_base64(message, opt);
}