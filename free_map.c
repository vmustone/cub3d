/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:11:09 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/08 08:12:25 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int i;

	i = 0;
	if (map)
	{
		while (map->map[i] != NULL)
		{
			if (map->map[i])
				free(map->map[i]);
			i++;
		}
		if(map->no)
			free(map->no);
		if(map->so)
			free(map->so);
		if(map->we)
			free(map->we);
		if(map->ea)
			free(map->ea);
		if(map->floor_color)
			free(map->floor_color);
		if(map->ceiling_color)
			free(map->ceiling_color);
		free(map);
	}
}