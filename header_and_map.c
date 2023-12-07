/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_and_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: villemustonen <villemustonen@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:16:44 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/07 06:16:24 by villemuston      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int isNumeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
    while (*str)
	{
        if (!ft_isdigit(*str))
            return (1);
        str++;
    }
    return (0);
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

void	rgb_to_int(char **rgb_array, int *save)
{
	int	rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (isNumeric(rgb_array[i]))
			return ;
		rgb[i] = ft_atoi(rgb_array[i]);
		if (rgb[i] > 255 || rgb < 0)
			return ;
		i++;
	}
	*save = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
}

void	remove_spaces(char *line, int len, char **save)
{
	line += len;
	while (*line == ' ')
		line++;
	*save = ft_substr(line, 0, ft_strlen(line));
}

void	rgb_string_to_int(char *input, int *save)
{
	char	*str;
	char	**nbr;

	str = NULL;
	remove_spaces(input, 2, &str);
	if (!str)
		return ;
	nbr = ft_split(str, ',');
	free(str);
	if (!nbr)
	{
		free_str(nbr);
		return ;
	}
	rgb_to_int(nbr, save);
	free_str(nbr);
}

int parse_header(t_map *map, char *line)
{
	int	i;
	
	i = ft_strlen(line);
	line[i - 1] = '\0';
	if (ft_strncmp(line, "NO ", 3) == 0)
		remove_spaces(line, 3, &map->no);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		remove_spaces(line, 3, &map->so);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		remove_spaces(line, 3, &map->we);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		remove_spaces(line, 3, &map->ea);
	else if (ft_strncmp(line, "F ", 2) == 0)
		rgb_string_to_int(line, &map->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		rgb_string_to_int(line, &map->ceiling_color);
	else
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}


int	read_map_header(t_map *map, int fd)
{
	char	*line;
	int		rows;
	
	rows = 0;
	while (rows < 6)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			break ;
		}
		if (ft_strlen(line) == 1)
		{
			free(line);
			continue ;
		}
		if (parse_header(map, line))
		{
			free(line);
			return (1);
		}
		rows++;
	}
	return (0);
}

int	read_map(t_list **map_info, t_map *map, int fd)
{
	char	*line;
	t_list	*lst;

	map->rows = 0;
	line = get_next_line(fd);
	while (line && ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		lst = ft_lstnew(line);
		if (!lst)
		{
			free(line);
			return (1);
		}
		ft_lstadd_back(map_info, lst);
		map->rows++;
		line = get_next_line(fd);
	}
	return (0);
}