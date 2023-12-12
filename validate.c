/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:22:10 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:12:11 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_header(t_map *map)
{
	if (!map->no || !map->so || !map->ea || !map->we || !map->floor_color
		|| !map->ceiling_color)
		return (1);
	else
		return (0);
}

static int	map_chars(t_map *map)
{
	char	*chars;
	int		x;
	int		y;

	chars = " 01NWSE";
	y = 0;
	if (map->map[y] == NULL)
		return (1);
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			if (!ft_strchr(chars, map->map[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	num_of_players(t_map *map)
{
	char	*chars;
	int		num_player;
	int		x;
	int		y;

	chars = "NWSE";
	num_player = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			if (ft_strchr(chars, map->map[y][x]))
			{
				map->player->pos_y = y;
				map->player->pos_x = x;
				num_player++;
			}
			x++;
		}
		y++;
	}
	return (num_player);
}

static int	check_walls(t_map *map)
{
	char	*edge;
	int		x;
	int		y;

	edge = save_edge_characters(map);
	if (check_edge_chars(edge))
		return (1);
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			if (map->map[y][x] == ' ')
			{
				if (check_edge_chars(get_surrounding_chars(map, y, x)))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate(t_map *map)
{
	if (check_header(map))
	{
		printf("1\n");
		return (1);
	}
	if (map_chars(map))
	{
		printf("2\n");
		return (1);
	}
	if (num_of_players(map) != 1)
	{
		printf("3\n");
		return (1);
	}
	if (check_walls(map))
	{
		printf("4\n");
		return (1);
	}
	return (0);
}
