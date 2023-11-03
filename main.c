/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:54:05 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/03 15:58:42 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(t_list **map_info, t_map *map, int fd)
{
	char	*line;
	t_list	*lst;
	while ((line = get_next_line(fd)))
	{
		if (ft_strlen(line) == 1)
		{
			free(line);
			continue;
		}
		lst = ft_lstnew(line);
		if (!lst)
		{
			free(line);
			return (1);
		}
		ft_lstadd_back(map_info, lst);
		map->rows++;
	}
	
	return 0;
}

int	file_name_check(char *argv)
{
	int			length;
	const char	*extension;
	
	length = ft_strlen(argv);
	extension = ".cub";
	if (length > 4 && ft_strcmp(argv + length - 4, extension) == 0)
		return (0);
	else
	{
		perror("Invalid map filename");
		return (1);
	}
}

int isNumeric(const char *str) {
    while (*str) {
        if (!ft_isdigit(*str) && *str != '-') {
            return 0;
        }
        str++;
    }
    return 1;
}

int *rgb_string_to_int(char *str) {
    int *ret = (int *)malloc(3 * sizeof(int));
    int count = 0;
    char temp[20];
    int temp_index = 0;
    int i = 0;

    while (str[i] != '\0' && count < 3)
	{
        if (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
		{
            temp[temp_index++] = str[i];
        }
		else if (temp_index > 0)
		{
            temp[temp_index] = '\0';
            if (isNumeric(temp))
                ret[count++] = ft_atoi(temp);
            temp_index = 0;
        }
        i++;
    }
    return ret;
}

int	map_header(t_map *map, int fd)
{
	char	*line;
	map->rows = 0;
	
	while (map->rows < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) == 1)
		{
			free(line);
			continue;
		}
		if (ft_strncmp(line, "NO ./", 5) == 0)
			map->no = line;
		if (ft_strncmp(line, "SO ./", 5) == 0)
			map->so = line;
		if (ft_strncmp(line, "WE ./", 5) == 0)
			map->we = line;
		if (ft_strncmp(line, "EA ./", 5) == 0)
			map->ea = line;
		if (ft_strncmp(line, "F ", 2) == 0)
			map->floor_color = rgb_string_to_int(line);
		if (ft_strncmp(line, "C ", 2) == 0)
			map->ceiling_color = rgb_string_to_int(line);
		map->rows++;
	}
	return (0);
}

int	parse_map(t_list *map_info, t_map *map)
{
	int	i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->rows - 6));
	while (i < (map->rows - 6))
	{
		map->map[i] = map_info->content;
		map_info = map_info->next;
		i++;
	}
	return (0);
}

int	parse(char *file, t_map *map)
{
	int		fd;
	t_list	*map_info;

	map_info = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if(map_header(map, fd) || read_map(&map_info, map, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	parse_map(map_info, map);
	free(map_info);
	return (0);
}

t_map	*init_map(char **argv)
{
	t_map	*map;
	
	if (file_name_check(argv[1]))
	{
		return (NULL);
	}
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (parse(argv[1], map))
	{
		return (NULL);
	}
	return (map);
}

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

int	main(int argc, char **argv)
{
	t_map	*game_map;
	
	game_map = init_map(argv);
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
	while (game_map->map[i])
	{
		printf("%s", game_map->map[i]);
		i++;
	}
	free_map(game_map);
	return (0);
}