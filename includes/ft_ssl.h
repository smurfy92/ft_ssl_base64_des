/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 11:08:41 by jtranchi          #+#    #+#             */
/*   Updated: 2018/08/09 12:04:38 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define F(b, c, d) ((b & c) | (~b & d))
#define G(b, c, d) ((b & d) | (c & ~d))
#define H(b, c, d) (b ^ c ^ d)
#define I(b, c, d) (c ^ (b | ~d))
#define LEFTROTATE(x, c) (x << c) | (x >> (32 - c))

#define DEBUG 1

#include <stdint.h>
#include <stdio.h>
#include "../libft/includes/libft.h"


typedef struct		s_mem
{
	char			*data;
	int				len;
}					t_mem;
