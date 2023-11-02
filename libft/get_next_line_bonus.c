/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:08:09 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/02 08:02:52 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *stash, char *buf)
{
	char	*temp;

	temp = ft_strjoin(stash, buf);
	free(stash);
	return (temp);
}

static char	*after_newline(char *stash, int *error)
{
	int		i;
	int		j;
	char	*end_line;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	end_line = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!end_line)
	{
		*error = 1;
		return (NULL);
	}
	i++;
	while (stash[i])
		end_line[j++] = stash[i++];
	free(stash);
	end_line[j] = '\0';
	return (end_line);
}

static char	*find_newline(char *stash)
{
	int		i;
	char	*line_ret;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line_ret = (char *)malloc(sizeof(char) * (i + 2));
	if (!line_ret)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line_ret[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line_ret[i++] = '\n';
	line_ret[i] = '\0';
	return (line_ret);
}

static char	*read_and_stash(int fd, char *ret)
{
	int		bytes_read;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(ret, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = 0;
		ret = join(ret, buf);
		if (!ret)
			return (NULL);
	}
	free(buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;
	int			error;

	error = 0;
	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(1, 1);
	if (!stash[fd])
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = find_newline(stash[fd]);
	stash[fd] = after_newline(stash[fd], &error);
	if (error)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
