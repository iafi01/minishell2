/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 00:34:23 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/04 00:34:25 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path2(char **paths, char *cmd)
{
	int		i;
	char	*folder;
	char	*path;

	i = 0;
	while (paths[i])
	{
		folder = ft_strjoin(paths[i], "/");
		path = ft_strjoin(folder, cmd);
		ft_str_delete(&folder);
		if (open(path, O_RDONLY) != -1)
			return (path);
		ft_str_delete(&path);
		i++;
	}
	if (is_path(cmd))
		if (open(cmd, O_RDONLY) != -1)
			return (cmd);
	if (!paths[i])
	{
		printf("Command not found\n");
		return (NULL);
	}
	return (NULL);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(*arr);
		*arr = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
