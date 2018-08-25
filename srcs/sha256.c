/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 13:49:20 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/25 16:24:52 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int g_m[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint64_t swap_uint64( uint64_t val )
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
	return (val << 32) | (val >> 32);
}

uint64_t	reverse_endian(uint64_t *b)
{
	uint8_t t;
	int i = -1;
	uint8_t *p;

	p = (uint8_t *)b;

	while (++i < 4)
	{
		t = p[i];
		p[i] = p[7 - i];
		p[7 - i] = t;
	}
	return ((uint64_t)p);
}

t_mem	*padding_sha256(t_mem *mem)
{
	t_mem		*message;
	size_t		newlen;
	size_t		len;
	uint64_t	bitlen;

	message = (t_mem *)malloc(sizeof(t_mem));
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	message->data = (unsigned char *)malloc(sizeof(unsigned char) *	newlen);
	message->len = newlen;
	memcpy(message->data, mem->data, mem->len);
	message->data[len] = (unsigned char)128;
	while (++len <= newlen)
		message->data[len] = 0;
	bitlen = swap_uint64(bitlen);
	memcpy(message->data + newlen, &bitlen, 8);
	return (message);
}

unsigned int *get_tab(unsigned char *offset)
{
	int i;
	i = -1;
	unsigned int *w;

	w = (unsigned int *)malloc(sizeof(unsigned int) * 64);
	while (++i < 64)
	{
		if (i < 16)
			w[i] = (offset[i * 4] << 24) |
				(offset[i * 4 + 1] << 16) |
				(offset[i * 4 + 2] << 8) |
				(offset[i* 4 + 3]);
		else
			w[i] = D(w[i - 2]) + w[i - 7] + C(w[i - 15]) + w[i - 16];
	}
	return (w);
}

void	init_mem(t_mem *mem)
{
	mem->h[0] = 0x6a09e667;
	mem->h[1] = 0xbb67ae85;
	mem->h[2] = 0x3c6ef372;
	mem->h[3] = 0xa54ff53a;
	mem->h[4] = 0x510e527f;
	mem->h[5] = 0x9b05688c;
	mem->h[6] = 0x1f83d9ab;
	mem->h[7] = 0x5be0cd19;
}

void	sha256_process(t_i *m, unsigned int w[64], int i)
{
	(*m).t = (*m).h + B((*m).e) +
		CH((*m).e,(*m).f,(*m).g) + g_m[i] + w[i];
	(*m).t2 = A((*m).a)+ MAJ((*m).a,(*m).b,(*m).c);
	(*m).h = (*m).g;
	(*m).g = (*m).f;
	(*m).f = (*m).e;
	(*m).e = (*m).d + (*m).t;
	(*m).d = (*m).c;
	(*m).c = (*m).b;
	(*m).b = (*m).a;
	(*m).a = (*m).t + (*m).t2;

}

void	hash_sha256(t_mem *mem)
{
	t_i		m;
	int		i;
	int		offset;
	unsigned int	*w;

	w = NULL;
	offset = 0;
	init_mem(mem);
	while (offset < mem->len)
	{
		w = get_tab((mem->data + offset));
		m.a = mem->h[0];
		m.b = mem->h[1];
		m.c = mem->h[2];
		m.d = mem->h[3];
		m.e = mem->h[4];
		m.f = mem->h[5];
		m.g = mem->h[6];
		m.h = mem->h[7];
		i = -1;
		while (++i < 64)
			sha256_process(&m, w, i);
		mem->h[0] += m.a;
		mem->h[1] += m.b;
		mem->h[2] += m.c;
		mem->h[3] += m.d;
		mem->h[4] += m.e;
		mem->h[5] += m.f;
		mem->h[6] += m.g;
		mem->h[7] += m.h;
		offset += 64;
	}
}
