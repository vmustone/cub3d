/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:54:21 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:31:17 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	num_of_columns(t_list *data, t_map *map)
{
	int	result;

	map->columns = 0;
	while (data)
	{
		result = ft_strlen(data->content);
		if (result > map->columns)
			map->columns = result - 1;
		data = data->next;
	}
}

static void	fill_with_spaces(char *row, int current_length, int target_length)
{
	while (current_length < target_length)
	{
		row[current_length] = ' ';
		current_length++;
	}
}

static int	check_newline(char *data)
{
	int	result;

	result = 0;
	while (*data != '\0' && *data != '\n')
	{
		data++;
		result++;
	}
	return (result);
}

int	parse_map(t_list *map_data, t_map *map)
{
	int	i;
	int	current_length;

	i = 0;
	num_of_columns(map_data, map);
	map->map = (char **)malloc(sizeof(char *) * map->rows + 1);
	if (!map->map)
		return (1);
	while (map_data)
	{
		current_length = check_newline(map_data->content);
		if (!ft_strcmp(map_data->content, "\n"))
			return (1);
		map->map[i] = (char *)malloc(sizeof(char) * map->columns + 1);
		if (!map->map[i])
			return (1);
		ft_bzero(map->map[i], map->columns + 1);
		ft_memcpy(map->map[i], map_data->content, current_length);
		if (current_length < map->columns)
			fill_with_spaces(map->map[i], current_length, map->columns);
		map_data = map_data->next;
		i++;
	}
	map->map[i] = NULL;
	return (0);
}
