/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:44:22 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/17 00:20:37 by villemuston      ###   ########.fr       */
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

void fill_with_spaces(char *row, int current_length, int target_length) {
    int	i;

	i = current_length;
	
	while (i < target_length)
	{
        row[i] = ' ';
		i++;
    }
	row[target_length] = '\n';
}

int	parse_map(t_list *map_data, t_map *map)
{
	int	i;

	i = 0;
	num_of_columns(map_data, map);
	map->map = (char **)malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		int current_length;

		current_length = ft_strlen(map_data->content) - 1;
        map->map[i] = map_data->content;
		if (current_length < map->columns)
			fill_with_spaces(map->map[i], current_length, map->columns);
		map_data = map_data->next;
		i++;
	}
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
