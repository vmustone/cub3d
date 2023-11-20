/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:22:10 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/20 15:55:09 by vmustone         ###   ########.fr       */
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

char	*saveEdgeCharacters(t_map *map)
{
    int edgeCharsLength = (map->rows + map->columns - 2) * 2;
    char *edgeChars = malloc(sizeof(char) * edgeCharsLength); // Allocate memory for edge characters

    int index = 0;
    int i = 0, j = 0;

    // Convert outer loop to while loop
    while (i < map->rows)
	{
        j = 0; // Reset inner loop counter
        // Convert inner loop to while loop
        while (j < map->columns)
		{
            // Check if current position is at the edge
            if (i == 0 || i == map->rows - 1 || j == 0 || j == map->columns - 1)
			{
                edgeChars[index++] = map->map[i][j];
            }
            j++; // Increment inner loop counter
        }
        i++; // Increment outer loop counter
    }

    edgeChars[index] = '\0'; // Null-terminate the string
	return (edgeChars);
}

int	checkEdgeChars(char *edge)
{
	while(*edge)
	{
		if (*edge != '1' && *edge != ' ')
			return (1);
		edge++;
	}
	return (0);
}

int check_walls(t_map *map)
{
	char	*edge;

	edge = saveEdgeCharacters(map);
	if (checkEdgeChars(edge))
		printf("invalid\n");
	printf("%s\n", edge);
	printf("%zu\n", ft_strlen(edge));
	return(0);
}

int	validate(t_map *map)
{
	if (check_header(map))
		return (1);
	if (map_chars(map))
		return (1);
	if (num_of_players(map) != 1)
		return (1);
	if (check_walls(map))
		return (1);
	
	return (0);
}