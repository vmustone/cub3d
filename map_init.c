/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:44:22 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/15 16:15:51 by vmustone         ###   ########.fr       */
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

int	num_of_columns(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[1] != '\0')
		i++;
	return (i);
}

int	parse_map(t_list *map_data, t_map *map)
{
	int	i;
	int tmp;
	i = 0;
	map->columns = 0;
	map->map = (char **)malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		if ((tmp = num_of_columns(map_data->content)) > map->columns)
			map->columns = tmp;
		map->map[i] = map_data->content;
		map_data = map_data->next;
		i++;
	}
	map->map[i] = NULL;
	return (0);
}

int	parse(char *file, t_map *map)
{
	int		fd;
	t_list	*map_data;

	map_data = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if(map_header(map, fd) || read_map(&map_data, map, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (parse_map(map_data, map))
		return (1);
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
	if (parse(argv[1], map)) //|| validate(map))
	{
		//free_map(map);
		return (NULL);
	}
	return (map);
}
