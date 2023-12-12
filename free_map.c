/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:11:09 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:36:06 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map, t_player *player)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < map->rows)
		{
			if (map->map[i])
				free(map->map[i]);
			i++;
		}
		if (map->no)
			free(map->no);
		if (map->so)
			free(map->so);
		if (map->we)
			free(map->we);
		if (map->ea)
			free(map->ea);
		free(map);
	}
	free(player);
}

void	free_str(char **str)
{
	int	i;

	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
