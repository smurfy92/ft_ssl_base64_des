/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:44:07 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/19 09:19:52 by jtranchi         ###   ########.fr       */
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

uint32_t g_h[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

void	print_output(t_mem *mem)
{
	uint8_t *p;

	p = (uint8_t *)&mem->h[0];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&mem->h[1];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&mem->h[2];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&mem->h[3];
	printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
}

int		print_usage(char *str)
{
	ft_putstr("usage: ");
	ft_putstr(str);
	ft_putendl(" [hash] [command options] [command arguments]");
	return (-1);
}

t_mem	*padding(t_mem *mem)
{
	t_mem		*message;
	size_t		newlen;
	size_t		len;
	uint32_t	bitlen;

	message = (t_mem *)malloc(sizeof(t_mem));
	message->h[0] = 0x67452301;
	message->h[1] = 0xefcdab89;
	message->h[2] = 0x98badcfe;
	message->h[3] = 0x10325476;
	len = mem->len;
	bitlen = len * 8;
	newlen = len + 1;
	while (newlen % 64 != 56)
		newlen++;
	message->data = (char *)malloc(sizeof(char) * newlen + 64);
	message->len = newlen;
	memcpy(message->data, mem->data, mem->len);
	message->data[len] = (char)128;
	while (++len <= newlen)
		message->data[len] = 0;
	ft_memcpy(message->data + newlen, &bitlen, 4);
	return (message);
}

void	md5_process(t_i *m, uint32_t *w, int i)
{
	if (i < 16)
		((*m).f = F((*m).b, (*m).c, (*m).d)) ?
			(*m).g = i : 0;
	else if (i < 32)
		((*m).f = G((*m).b, (*m).c, (*m).d)) ?
			((*m).g = (5 * i + 1) % 16) : 0;
	else if (i < 48)
		((*m).f = H((*m).b, (*m).c, (*m).d)) ?
			((*m).g = (3 * i + 5) % 16) : 0;
	else
		((*m).f = I((*m).b, (*m).c, (*m).d)) ?
			((*m).g = (7 * i) % 16) : 0;
	(*m).t = (*m).d;
	(*m).d = (*m).c;
	(*m).c = (*m).b;
	(*m).b = (*m).b +
		LEFTROTATE(((*m).a + (*m).f + g_k[i] + w[(*m).g]), g_r[i]);
	(*m).a = (*m).t;
}

void	hash_md5(t_mem *mem)
{
	int			offset;
	int			i;
	t_i			m;
	uint32_t	*w;

	offset = 0;
	while (offset < mem->len)
	{
		w = (uint32_t*)(mem->data + offset);
		m.a = mem->h[0];
		m.b = mem->h[1];
		m.c = mem->h[2];
		m.d = mem->h[3];
		i = -1;
		while (++i < 64)
			md5_process(&m, w, i);
		mem->h[0] += m.a;
		mem->h[1] += m.b;
		mem->h[2] += m.c;
		mem->h[3] += m.d;
		offset += 64;
	}
}

t_opt	*add_arg(t_opt *opt, char *str)
{
	t_arg *arg;
	t_arg *tmp;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->str = ft_strdup(str);
	arg->next = NULL;
	if (opt->arg == NULL)
		opt->arg = arg;
	else
	{
		tmp = opt->arg;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = arg;
	}
	return (opt);
}

t_opt	*check_options(t_opt *opt, char *str)
{
	int i; 
	int b;

	i = -1;
	b = 0;
	while (str[++i])
	{
		if (str[0] == '-' && opt->arg == NULL)
			b = 1;
		else
			return (add_arg(opt, str));
		if (b)
		{
			(str[i] == 'p') ? (opt->p = 1) : 0;
			(str[i] == 'q') ? (opt->q = 1) : 0;
			(str[i] == 'r') ? (opt->r = 1) : 0;
			(str[i] == 's') ? (opt->s = 1) : 0;
		}
	}
	return (opt);
}


t_opt	*check_opt(t_opt *opt, char **argv)
{
	int i;

	i = 1;
	opt = (t_opt*)malloc(sizeof(t_opt));
	opt->hash = ft_strdup(argv[1]);
	opt->p = 0;
	opt->q = 0;
	opt->r = 0;
	opt->s = 0;
	opt->arg = NULL;
	if (ft_strequ(opt->hash, "md5") != 1 && ft_strequ(opt->hash, "sha256") != 1)
	{
		ft_putendl("invalid hash algorithm");
		exit(-1);
	}
	while (argv[++i])
		opt = check_options(opt, argv[i]);
	return (opt);
}

void	print_debug(t_opt *opt)
{

	printf("opt->hash %s\n", opt->hash);
	printf("opt->p %d\n", opt->p);
	printf("opt->q %d\n", opt->q);
	printf("opt->r %d\n", opt->r);
	printf("opt->s %d\n", opt->s);
	t_arg *arg;
	arg = opt->arg;
	while (arg)
	{
		printf("arg ->%s\n" ,arg->str);
		arg = arg->next;
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

int		main(int argc, char **argv)
{
	t_mem	*message;
	t_opt	*opt;
	t_arg	*arg;
	int		fd;

	message = NULL;
	opt = NULL;
	int i = -1;
	while (argv[++i])
		printf("argv -> %s\n",argv[i]);
	if (argc < 2)
		return (print_usage(argv[0]));
	opt = check_opt(opt, argv);
	print_debug(opt);
	if (!isatty(0) || argc < 3)
	{
		message = read_fd(0);
		if (opt->p)
			ft_putstr(message->data);
		message = padding(message);
		hash_md5(message);
		print_output(message);
		printf("\n");
	}
	if (argc >= 3)
	{
		arg = opt->arg;
		while(arg)
		{
			if ((fd = open(arg->str, O_RDONLY)) != -1)
			{
				message = read_fd(fd);
				message = padding(message);	
				hash_md5(message);

				(!opt->r && !opt->q) ? (printf("MD5 (%s) = ", arg->str)) : 0;
				print_output(message);
				(opt->r && !opt->q) ? (printf(" %s", arg->str)) : 0;
				printf("\n");
			}
			else
			{
				if (opt->s)
				{
					message = (t_mem*)malloc(sizeof(t_mem));
					message->data = ft_strdup(arg->str);
					message->len = ft_strlen(message->data);
					message = padding(message);
					hash_md5(message);
					(!opt->r && !opt->q) ? (printf("MD5 (\"%s\") = ", arg->str)) : 0;
					print_output(message);
					(opt->r && !opt->q) ? (printf(" \"%s\"", arg->str)) : 0;
				printf("\n");
				}else
					(!opt->q) ? (write_file_error(arg->str, opt)) : 0;
			}
			arg = arg->next;	
		}
	}
	return (0);
}
