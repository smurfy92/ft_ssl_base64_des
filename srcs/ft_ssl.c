/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:44:07 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/09 15:25:45 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"


int32_t g_r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21};

int32_t g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

uint32_t g_h[4] = {0x67452301,0xefcdab89,0x98badcfe,0x10325476};

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

int		print_usage(char *str)
{
	ft_putstr("usage: ");
	ft_putstr(str);
	ft_putstr(" [hash] [command options] [command arguments]");
	return (-1);
}

t_mem	*padding(char *str)
{
	t_mem *message;
	size_t newlen;
	size_t len;
	uint32_t bitlen;

	message = (t_mem *)malloc(sizeof(t_mem));
	len = ft_strlen(str);
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	message->data = (char *)malloc(sizeof(char) * newlen + 64);
	message->len = newlen;
#if (DEBUG == 1)
	printf("size malloced -> %zu\n", newlen + 8);
#endif
	memcpy(message->data, str, len);
	message->data[len] = (char)128;
	while (++len <= newlen)
		message->data[len] = 0;
	ft_memcpy(message->data + newlen, &bitlen, 4);
	return (message);
}

void	hash_md5(t_mem *mem)
{
	int offset;
	int i;
	t_i m;
	uint32_t *w;

	offset = 0;
	while (offset < mem->len)
	{
		w = (uint32_t*)(mem->data + offset);
		m.a = g_h[0];
		m.b = g_h[1];
		m.c = g_h[2];
		m.d = g_h[3];
		i = -1;
		while (++i < 64)
		{
			if (i < 16)
			{
				m.f = F(m.b, m.c, m.d);
				m.g = i;
			}
			else if (i < 32)
			{
				m.f = G(m.b, m.c, m.d);
				m.g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				m.f = H(m.b, m.c, m.d);
				m.g = (3 * i + 5) % 16;
			}
			else
			{
				m.f = I(m.b, m.c, m.d);
				m.g = (7 * i) % 16;
			}
			m.t = m.d;
			m.d = m.c;
			m.c = m.b;
			m.b = m.b + LEFTROTATE((m.a + m.f + g_k[i] + w[m.g]), g_r[i]);
			m.a = m.t;
		}
		ft_putstr("ici\n");
		g_h[0] += m.a;
		g_h[1] += m.b;
		g_h[2] += m.c;
		g_h[3] += m.d;
		offset += 64;
	}
	uint8_t *p;
	p=(uint8_t *)&g_h[0];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

	p=(uint8_t *)&g_h[1];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

	p=(uint8_t *)&g_h[2];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

	p=(uint8_t *)&g_h[3];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
}

int		main(int argc, char **argv)
{
	t_mem *message;

	if (argc < 2)
		return (print_usage(argv[0]));
	message = padding(argv[1]);
	hash_md5(message);
	return (0);
}
