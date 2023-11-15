/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_and_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:16:44 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/15 16:23:06 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int isNumeric(const char *str)
{
    while (*str)
	{
        if (!ft_isdigit(*str) && *str != '-')
            return (0);
        str++;
    }
    return (1);
}

int *rgb_string_to_int(char *str) {
    int		*ret;
    int		count;
    char	temp[20];
    int		temp_index;
    int		i;

	ret = (int *)malloc(3 * sizeof(int));
	count = 0;
	temp_index = 0;
	i = 0;

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
	int		rows;
	
	rows = 0;
	while (rows < 6)
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
		else if (ft_strncmp(line, "SO ./", 5) == 0)
			map->so = line;
		else if (ft_strncmp(line, "WE ./", 5) == 0)
			map->we = line;
		else if (ft_strncmp(line, "EA ./", 5) == 0)
			map->ea = line;
		else if (ft_strncmp(line, "F ", 2) == 0)
			map->floor_color = rgb_string_to_int(line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			map->ceiling_color = rgb_string_to_int(line);
		else
			return (1);
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