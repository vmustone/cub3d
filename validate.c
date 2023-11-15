/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:22:10 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/15 15:08:37 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_header(t_map *map)
{
	if (!map->no || !map->so || !map->ea || !map->we || !map->floor_color
		|| !map->ceiling_color)
		return (1);
	else
		return (0);
}

int	map_chars(t_map *map)
{
	char	*chars = " 01NWSE";
	int	x;
	int y;

	y = 0;
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

int	num_of_players(t_map *map)
{
	char	*chars = "NWSE";
	int		player;
	int		x;
	int		y;

	player = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			if (ft_strchr(chars, map->map[y][x]))		
				player++;
			x++;
		}
		y++;
	}
	return (player);
}


int check_walls(t_map *map)
{
   return (1);
}

int	validate(t_map *map)
{
	if (check_header(map))
		return (1);
	if (map_chars(map))
		return (1);
	if (num_of_players(map) != 1)
		return (1);
	if (!check_walls(map))
		return (1);
	
	return (0);
}