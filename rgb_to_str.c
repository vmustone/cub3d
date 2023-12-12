/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:00:42 by vmustone          #+#    #+#             */
/*   Updated: 2023/12/12 16:26:25 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	isnumeric(const char *str)
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

static void	rgb_to_int(char **rgb_array, int *save)
{
	int	rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (isnumeric(rgb_array[i]))
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
