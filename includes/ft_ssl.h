/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 11:08:41 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/18 17:44:34 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_SSL_H
# define FT_SSL_H

# define F(b, c, d) ((b & c) | (~b & d))
# define G(b, c, d) ((b & d) | (c & ~d))
# define H(b, c, d) (b ^ c ^ d)
# define I(b, c, d) (c ^ (b | ~d))
# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

# define DEBUG 1
# define BUFFER 1024
# include <stdint.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include <errno.h>
# include <string.h>


typedef struct		s_mem
{
	char			*data;
	uint32_t		h[4];
	int				len;
}					t_mem;

typedef struct		s_arg
{
	char			*str;
	struct s_arg    *next;
}					t_arg;

typedef struct		s_opt
{
	char			*hash;
	struct s_arg	*arg;
	int				p;
	int				q;
	int				r;
	int				s;
}					t_opt;

typedef struct		s_i
{
	int				a;
	int				b;
	int				c;
	int				d;
	int				f;
	int				g;
	int				t;
}					t_i;

void	ft_free_mem(t_mem *mem);
t_mem	*ft_memjoin(t_mem *dest, t_mem *src);
t_mem	*read_fd(int fd);
void	write_fd(int fd, t_mem *mem);

#endif
