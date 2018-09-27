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

void		push_arg_list(t_opt *opt, t_arg *arg)
{
	t_arg *tmp;

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
}

t_opt		*add_arg_padding(t_opt *opt, char *str)
{
	str = padding_key(str);
	if (opt->k)
	{
		opt->key = ft_atoi_base(str, 16);
		opt->k = 0;
	}
	if (opt->v)
	{
		opt->vector = ft_atoi_base(str, 16);
		opt->v = 0;
	}
	if (opt->p)
	{

		opt->pass = ft_atoi_base(str, 16);
		opt->p = 0;
	}
	if (opt->s)
	{
		opt->salt = ft_atoi_base(str, 16);
		opt->s = 0;
	}
	return (opt);
}

t_opt		*check_args(t_opt *opt, char *str)
{
	if (opt->k || opt->v || opt->p)
		return (add_arg_padding(opt, str));
	return (NULL);
}

t_opt		*add_arg(t_opt *opt, char *str)
{
	t_arg *arg;

	if ((opt = check_args(opt, str)))
		return (opt);
	if (opt->hash == 2)
	{
		if (!opt->i || opt->arg)
			return (opt);
		opt->i = 0;
	}
	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->str = ft_strdup(str);
	arg->is_string = 0;
	if (opt->s)
	{
		arg->is_string = 1;
		opt->s = 0;
	}
	push_arg_list(opt, arg);
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
		if (opt->o)
		{
			opt->output = ft_strdup(str);
			continue;
		}
		if (str[0] == '-')
			b = 1;
		else
			return (add_arg(opt, str));
		if (b)
			set_flags(opt, str[i]);
	}
	return (opt);
}

t_opt		*check_opt(t_opt *opt, char **argv)
{
	int i;

	i = 1;
	opt = (t_opt*)malloc(sizeof(t_opt));
	opt->hash = get_hash_index(argv[1]);
	opt_init(opt);
	if (opt->hash == -1)
	{
		ft_putendl("ft_ssl: invalid hash algorithm");
		ft_putendl("\nMessage Digest Commands:\nmd5\nsha256");
		exit(-1);
	}
	while (argv[++i])
		check_options(opt, argv[i]);
	return (opt);
}
