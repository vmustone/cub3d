/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:12:59 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:38:04 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			rows;
	int			columns;
	int			floor_color;
	int			ceiling_color;
	t_player	*player;
}				t_map;

void	free_map(t_map *map, t_player *player);
t_map	*init_map(char **argv);
int		read_map_header(t_map *map, int fd);
int		read_map(t_list **map_info, t_map *map, int fd);
int		validate(t_map *map);
char	*get_surrounding_chars(t_map *map, int y, int x);
int		check_edge_chars(char *str);
char	*save_edge_characters(t_map *map);
int		parse_map(t_list *map_data, t_map *map);
void	free_str(char **str);
void	rgb_string_to_int(char *input, int *save);
void	remove_spaces(char *line, int len, char **save);

#endif
