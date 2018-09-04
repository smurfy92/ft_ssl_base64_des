/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 09:51:36 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/28 15:25:15 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_opt		*add_arg(t_opt *opt, char *str)
{
	t_arg *arg;
	t_arg *tmp;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->str = ft_strdup(str);
	arg->is_string = 0;
	if (opt->s)
	{
		arg->is_string = 1;
		opt->s = 0;
	}
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

t_opt		*check_options(t_opt *opt, char *str)
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
			(str[i] == 'd') ? (opt->d = 1) : 0;
			if (str[i] == 's')
			{
				opt->s = 1;
			}
		}
	}
	return (opt);
}

int			get_hash_index(char *hash)
{
	int i;

	i = -1;
	while (HASH[++i])
	{
		if (ft_strequ(HASH[i], hash))
			return (i);
	}
	return (-1);
}

t_opt		*check_opt(t_opt *opt, char **argv)
{
	int i;

	i = 1;
	opt = (t_opt*)malloc(sizeof(t_opt));
	opt->hash = get_hash_index(argv[1]);
	opt->p = 0;
	opt->q = 0;
	opt->r = 0;
	opt->s = 0;
	opt->d = 0;
	opt->stdin = 1;
	opt->arg = NULL;
	if (opt->hash == -1)
	{
		ft_putendl("ft_ssl: invalid hash algorithm");
		ft_putendl("\nMessage Digest Commands:\nmd5\nsha256");
		exit(-1);
	}
	while (argv[++i])
		opt = check_options(opt, argv[i]);
	return (opt);
}

void		init_mem(t_mem *mem)
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
