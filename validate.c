/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:22:10 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/27 16:12:15 by vmustone         ###   ########.fr       */
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

char	*save_edge_characters(t_map *map)
{
    char *edge_chars;
    int index;
    int y;
	int	x;

	edge_chars = malloc(sizeof(char) * ((map->rows + map->columns - 2) * 2));
	if (!edge_chars)
		return (NULL);
	index = 0;
	y = 0;
    while (y < map->rows)
	{
        x = 0;
        while (x < map->columns)
		{
            if (y == 0 || y == map->rows - 1 || x == 0 || x == map->columns - 1)
                edge_chars[index++] = map->map[y][x];
            x++;
        }
        y++;
    }
    edge_chars[index] = '\0';
	return (edge_chars);
}

int	check_edge_chars(char *edge)
{
	while(*edge)
	{
		if (*edge != '1' && *edge != ' ')
			return (1);
		edge++;
	}
	return (0);
}

char *get_surrounding_chars(t_map *map, int y, int x)
{
    char *adj_chr;
    int dx, dy;

    adj_chr = (char *)malloc(sizeof(char) * 9);
    if (!adj_chr)
        return NULL;
    int index = 0;
    dy = -1;
    while (dy <= 1)
	{
        dx = -1;
        while (dx <= 1)
		{
            int newX = x + dx;
            int newY = y + dy;

            if (newX >= 0 && newX < map->columns && newY >= 0 && newY < map->rows)
			{
                adj_chr[index++] = map->map[newY][newX];
            }
            dx++;
        }
        dy++;
    }
    adj_chr[index] = '\0';
    return (adj_chr);
}


int check_walls(t_map *map)
{
	char	*edge;
	int	x;
	int	y;

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
	return(0);
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