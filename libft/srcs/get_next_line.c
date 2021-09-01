/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmizzoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:09:07 by lmizzoni          #+#    #+#             */
/*   Updated: 2021/01/22 11:09:10 by lmizzoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_line(char *s[], int fd)
{
	char	*tmp;

	if (ft_is_in_str('\n', s[fd]) >= 0)
	{
		tmp = s[fd];
		s[fd] = ft_substr(s[fd], ft_is_in_str('\n', s[fd]) + 1,
				ft_strlen(s[fd]));
		free(tmp);
	}
	else if (ft_strlen(s[fd]) > 0)
		ft_str_delete(&s[fd]);
	else
	{
		ft_str_delete(&s[fd]);
		return (FINISH);
	}
	return (SUCCESS);
}

char	*alloc(char **s, int fd)
{
	s[fd] = ft_calloc(1, sizeof(char *));
	return (s[fd]);
}

int	get_next_line(int fd, char **line)
{
	static char		*s[10240];
	char			buf[BUFFER_SIZE + 1];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (ERROR);
	if (!s[fd] && !alloc(s, fd))
		return (ERROR);
	ret = 1;
	while ((ft_is_in_str('\n', s[fd])) < 0 && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		tmp = s[fd];
		s[fd] = ft_strjoin(s[fd], buf);
		free(tmp);
	}
	if (s[fd])
		*line = ft_substr(s[fd], 0, ft_strlen_c(s[fd], '\n'));
	if (!handle_line(s, fd))
		return (FINISH);
	return (SUCCESS);
}
