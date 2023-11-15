/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:12:59 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/15 12:23:52 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		rows;
	int		columns;
	int		*floor_color;
	int		*ceiling_color;
}				t_map;

void	free_map(t_map *map);
t_map	*init_map(char **argv);
int		map_header(t_map *map, int fd);
int		read_map(t_list **map_info, t_map *map, int fd);
int		validate(t_map *map);
int		check_header(t_map *map);
int		map_chars(t_map *map);
int		validate(t_map *map);

#endif