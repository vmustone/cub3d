/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:54:05 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:41:23 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*game_map;
	int		i;

	if (argc != 2)
		return (printf("wrong input\n"));
	game_map = init_map(argv);
	if (!game_map)
		return (1);
	printf("%s\n", game_map->no);
	printf("%s\n", game_map->so);
	printf("%s\n", game_map->we);
	printf("%s\n", game_map->ea);
	printf("floor: %d\n", game_map->floor_color);
	printf("ceiling: %d\n", game_map->ceiling_color);
	i = 0;
	printf("rows: %d\n", game_map->rows);
	printf("columns: %d\n", game_map->columns);
	while (game_map->map[i])
	{
		printf("%s\n", game_map->map[i]);
		i++;
	}
	printf("player-x: %d\n", game_map->player->pos_x);
	printf("player-y: %d\n", game_map->player->pos_y);
	free_map(game_map, game_map->player);
	return (0);
}
