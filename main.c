/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:54:05 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/02 15:12:58 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	read_map_file(char **argv)
{
	t_map	map;
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error while openin map.\n");
		exit (1);
	}
	map.rows = 0;
	while ((line = get_next_line(fd)))
		map.rows++;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error while openin map.\n");
		exit (1);
	}
	map.map = (char **)malloc(sizeof(char *) * map.rows);
	int	i;
	i = 0;
	while ((map.map[i] = get_next_line(fd)))
		i++;
	close(fd);
	return map;
}

int	file_name_check(char **argv)
{
	int			length;
	const char	*extension;
	
	length = ft_strlen(argv[1]);
	extension = ".cub";
	if (length > 4 && ft_strcmp(argv[1] + length - 4, extension) == 0)
		return (0);
	else
	{
		perror("Invalid map filename");
		return (1);
	}
}

int	valid_map(t_map *map)
{
}

int	main(int argc, char **argv)
{
	t_map	game_map;
	
	if (file_name_check(argv) == 0)
		game_map = read_map_file(argv);
	if (valid_map(&game_map) == 0)
	{
		printf("valid map\n");
	}
	int i = 0;
	while (i < game_map.rows)
	{
		printf("%s", game_map.map[i]);
		i++;
	}
	printf("\n");
	
	return (0);
}