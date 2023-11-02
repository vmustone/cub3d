/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmustone <vmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:20:23 by vmustone          #+#    #+#             */
/*   Updated: 2023/11/02 08:08:14 by vmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	u;

	str = (char *) s;
	u = (char) c;
	while (*str != '\0')
		str++;
	while (*str != u && str > s)
		str--;
	if (*str == u)
		return (str);
	return (0);
}
