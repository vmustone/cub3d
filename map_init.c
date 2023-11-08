/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:44:22 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/08 08:39:01 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_name_check(char *argv)
{
	int			length;
	const char	*extension;
	
	length = ft_strlen(argv);
	extension = ".cub";
	if (length > 4 && ft_strcmp(argv + length - 4, extension) == 0)
		return (0);
	else
	{
		perror("Invalid map filename");
		return (1);
	}
}

int	parse_map(t_list *map_info, t_map *map)
{
	int	i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->rows - 6));
	while (i < (map->rows - 6))
	{
		map->map[i] = map_info->content;
		map_info = map_info->next;
		i++;
	}
	map->map[i] = NULL;
	return (0);
}

int	parse(char *file, t_map *map)
{
	int		fd;
	t_list	*map_info;

	map_info = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if(map_header(map, fd) || read_map(&map_info, map, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	parse_map(map_info, map);
	return (0);
}

t_map	*init_map(char **argv)
{
	t_map	*map;
	
	if (file_name_check(argv[1]))
	{
		return (NULL);
	}
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (parse(argv[1], map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
