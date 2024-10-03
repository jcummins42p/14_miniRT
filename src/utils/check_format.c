/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:20:44 by akretov           #+#    #+#             */
/*   Updated: 2024/10/03 18:10:03 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_format(int argc, char **argv)
{
	int			x;
	size_t		len;
	size_t		ext_len;
	const char	*format;

	x = 1;
	format = ".rt";
	len = ft_strlen(format);
	while (x < argc)
	{
		ext_len = ft_strlen(argv[x]);
		if (len > ext_len || ft_strncmp(&argv[x][ext_len - len], format, len) != 0)
			return 1;
		x++;
	}
	return 0;
}
