/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:43:37 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/23 11:43:54 by lmizzoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# define SUCCESS 1
# define FINISH 0
# define ERROR -1

# include "libft.h"
# include <fcntl.h>

int		get_next_line(int fd, char **line);

#endif
