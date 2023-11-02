/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:58:22 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/02 08:07:34 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst && dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst && *dst != '\0' && dstsize > i)
	{
		dst++;
		i++;
	}
	while (*src != '\0')
	{
		i++;
		if (dstsize > i)
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	if (dst)
		*dst = '\0';
	return (i);
}
