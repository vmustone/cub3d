/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:54:05 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/08 11:57:00 by vmustone         ###   ########.fr       */
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

int	check_map(t_map *map)
{
	
}

int	validate(t_map *map)
{
	if (check_header(map))
		return (1);
	if (check_map(map))
		return (1);
}

int	main(int argc, char **argv)
{
	t_map	*game_map;
	
	game_map = init_map(argv);
	if (!game_map)
		return (1);
	printf("%s", game_map->no);
	printf("%s", game_map->so);
	printf("%s", game_map->we);
	printf("%s", game_map->ea);

	int i = 0;
	while (i < 3)
	{
		printf("floor; %d\n", game_map->floor_color[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("ceiling; %d\n", game_map->ceiling_color[i]);
		i++;
	}
	i = 0;
	printf("rows %d\n", game_map->rows);
	while (game_map->map[i] != NULL)
	{
		printf("%s", game_map->map[i]);
		i++;
	}
	free_map(game_map);
	return (0);
}