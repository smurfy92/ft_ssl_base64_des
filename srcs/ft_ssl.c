/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:44:07 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/21 17:02:24 by jtranchi         ###   ########.fr       */
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

int					reverse_endian(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

t_mem	*padding_sha256(t_mem *mem)
{
	t_mem		*message;
	size_t		newlen;
	size_t		len;
	uint32_t	bitlen;

	message = (t_mem *)malloc(sizeof(t_mem));
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	message->data = (unsigned char *)malloc(sizeof(unsigned char) * newlen + 64);
	message->len = newlen;
	memcpy(message->data, mem->data, mem->len);
	message->data[len] = (unsigned char)128;
	while (++len <= newlen)
		message->data[len] = 0;
	printf("newlen %zu\n", newlen);
	ft_memcpy(message->data + newlen + 7, &bitlen, 4);
	return (message);
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

void	hash_sha256(t_mem *mem)
{
	//int 	offset;
	t_i		m;
	int		i;
	unsigned int	w[64];

	init_mem(mem);
	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			w[i] = (mem->data[i * 4] << 24) | (mem->data[i * 4 + 1] << 16) | (mem->data[i * 4 + 2] << 8) | (mem->data[i* 4 + 3]);
		else
			w[i] = D(w[i - 2]) + w[i - 7] + C(w[i - 15]) + w[i - 16];
	}
		m.a = mem->h[0];
		m.b = mem->h[1];
		m.c = mem->h[2];
		m.d = mem->h[3];
		m.e = mem->h[4];
		m.f = mem->h[5];
		m.g = mem->h[6];
		m.h = mem->h[7];
	printf("mem->h[0] %d\n", mem->h[0]);
	printf("mem->h[1] %d\n", mem->h[1]);
	printf("mem->h[2] %d\n", mem->h[2]);
	printf("mem->h[3] %d\n", mem->h[3]);
	printf("mem->h[4] %d\n", mem->h[4]);
	printf("mem->h[5] %d\n", mem->h[5]);
	printf("mem->h[6] %d\n", mem->h[6]);
	printf("mem->h[7] %d\n", mem->h[7]);
		i = -1;
		while (++i < 64)
		{
			m.t = m.h + B(m.e) + CH(m.e,m.f,m.g) + g_m[i] + w[i];
			m.t2 = A(m.a)+ MAJ(m.a,m.b,m.c);
			m.h = m.g;
			m.g = m.f;
			m.f = m.e;
			m.e = m.d + m.t;
			m.d = m.c;
			m.c = m.b;
			m.b = m.a;
			m.a = m.t + m.t2;
				printf("a -> %d\n", m.a);
				printf("b -> %d\n", m.b);
				printf("c -> %d\n", m.c);
				printf("d -> %d\n", m.d);
				printf("e -> %d\n", m.e);
				printf("f -> %d\n", m.f);
				printf("g -> %d\n", m.g);
				printf("h -> %d\n", m.h);
				printf("t -> %d\n", m.t);
				printf("t2 -> %d\n", m.t2);
		}
		mem->h[0] += m.a;
		mem->h[1] += m.b;
		mem->h[2] += m.c;
		mem->h[3] += m.d;
		mem->h[4] += m.e;
		mem->h[5] += m.f;
		mem->h[6] += m.g;
		mem->h[7] += m.h;
	printf("mem->h[0] %d\n", mem->h[0]);
	printf("mem->h[1] %d\n", mem->h[1]);
	printf("mem->h[2] %d\n", mem->h[2]);
	printf("mem->h[3] %d\n", mem->h[3]);
	printf("mem->h[4] %d\n", mem->h[4]);
	printf("mem->h[5] %d\n", mem->h[5]);
	printf("mem->h[6] %d\n", mem->h[6]);
	printf("mem->h[7] %d\n", mem->h[7]);
	for (i = 0; i < 4; ++i) {
		mem->data[i]      = (mem->h[0] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 4]  = (mem->h[1] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 8]  = (mem->h[2] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 12] = (mem->h[3] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 16] = (mem->h[4] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 20] = (mem->h[5] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 24] = (mem->h[6] >> (24 - i * 8)) & 0x000000ff;
		mem->data[i + 28] = (mem->h[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

void	handle_stdin(t_opt *opt)
{
	t_mem *message;

	message = NULL;
	message = read_fd(0);
	if (opt->p)
		ft_putstr((char *)message->data);
	if (ft_strequ(opt->hash, "md5") == 1)
	{
		message = padding(message);
		hash_md5(message);
		print_output(message);
	}
	if (ft_strequ(opt->hash, "sha256") == 1)
	{
		message = padding_sha256(message);
		hash_sha256(message);
		print_output_sha256(message);
	}
	ft_putchar('\n');
}
void	write_prefix(t_opt *opt, char *str)
{
	if (ft_strequ(opt->hash, "md5") == 1)
		ft_putstr("MD5 (");
	if (ft_strequ(opt->hash, "sha256") == 1)
		ft_putstr("SHA256 (");
	ft_putstr(str);
	ft_putstr(") = ");
}
void	write_suffix(char *str)
{
	ft_putchar(' ');
	ft_putstr(str);
}

void	hash(t_opt *opt, t_mem *message, t_arg *arg)
{
	if (ft_strequ(opt->hash, "md5") == 1)
	{
		message = padding(message);
		hash_md5(message);
		(!opt->r && !opt->q) ? (write_prefix(opt, arg->str)) : 0;
		print_output(message);
		(opt->r && !opt->q) ? (write_suffix(arg->str)) : 0;
	}
	ft_putchar('\n');
}

void	handle_string(t_opt *opt, t_arg *arg)
{
	t_mem *message;

	message = (t_mem*)malloc(sizeof(t_mem));
	message->data = (unsigned char*)ft_strdup(arg->str);
	message->len = ft_strlen((char *)message->data);
	hash(opt, message, arg);
}

void	handle_args(t_opt *opt)
{
	t_arg	*arg;
	t_mem	*message;
	int		fd;

	message = NULL;
	arg = opt->arg;
	while(arg)
	{
		if ((fd = open(arg->str, O_RDONLY)) != -1)
		{
			message = read_fd(fd);
			hash(opt, message, arg);
		}
		else
		{
			if (opt->s)
				handle_string(opt, arg);
			else
				(!opt->q) ? (write_file_error(arg->str, opt)) : 0;
		}
		arg = arg->next;	
	}
}

int		main(int argc, char **argv)
{
	t_opt	*opt;

	opt = NULL;
	if (argc < 2)
		return (print_usage(argv[0]));
	opt = check_opt(opt, argv);
	if (!isatty(0) || argc < 3)
		handle_stdin(opt);
	if (argc >= 3)
		handle_args(opt);
	return (0);
}
