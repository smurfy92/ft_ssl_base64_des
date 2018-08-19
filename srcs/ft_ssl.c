/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:44:07 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/19 10:18:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	handle_stdin(t_opt *opt)
{
	t_mem *message;

	message = NULL;
	message = read_fd(0);
	if (opt->p)
		ft_putstr(message->data);
	message = padding(message);
	hash_md5(message);
	print_output(message);
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
			message = padding(message);	
			hash_md5(message);
			(!opt->r && !opt->q) ? (printf("MD5 (%s) = ", arg->str)) : 0;
			print_output(message);
			(opt->r && !opt->q) ? (printf(" %s", arg->str)) : 0;
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
			}else
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
