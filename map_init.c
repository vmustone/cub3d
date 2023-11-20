/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:44:22 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/20 13:39:44 by vmustone         ###   ########.fr       */
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

void	num_of_columns(t_list *data, t_map *map)
{
	int	result;
	
	map->columns = 0;
	while (data)
	{
		if ((result = ft_strlen(data->content)) > map->columns)
			map->columns = result - 1;
		data = data->next;
	}
}

void fill_with_spaces(char *row, int current_length, int target_length)
{
	while (current_length < target_length)
	{
        row[current_length] = ' ';
		current_length++;
    }
}

int	check_newline(char *data)
{
	int	result;

	result = ft_strlen(data);
	while (*data)
	{
		if (*data == '\n')
			return (result - 1);
		data++;
	}
	return (result);
}

int	parse_map(t_list *map_data, t_map *map)
{
	int	i;

	i = 0;
	num_of_columns(map_data, map);
	map->map = (char **)malloc(sizeof(char *) * (map->rows));
	while (map_data)
	{
		int current_length;
		
		current_length = check_newline(map_data->content);
		if (!ft_strcmp(map_data->content, "\n"))
			return (1);
		map->map[i] = (char *)malloc(sizeof(char) * (map->columns));
        map->map[i] = map_data->content;
		if (current_length < map->columns)
			fill_with_spaces(map->map[i], current_length, map->columns);
		map->map[i][map->columns] = '\0';
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
	if(read_map_header(map, fd) || read_map(&map_data, map, fd))
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
	if (parse(argv[1], map) || validate(map))
	{
		printf("invalid map\n");
		free_map(map);
		return (NULL);
	}
	return (map);
}
