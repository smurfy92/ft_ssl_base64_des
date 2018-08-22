/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:44:07 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/22 14:58:28 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

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
	if (ft_strequ(opt->hash, "sha256") == 1)
	{
		message = padding_sha256(message);
		hash_sha256(message);
		(!opt->r && !opt->q) ? (write_prefix(opt, arg->str)) : 0;
		print_output_sha256(message);
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
