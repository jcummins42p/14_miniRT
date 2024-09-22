/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:57:27 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/22 12:11:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_color(char *pre, char *mid, char *post, int color)
{
	int	rgb[3];

	if (!pre || !mid || ! post)
		return ;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	printf(KDEF "%s", pre);
	printf("\033[38;2;%d;%d;%dm", rgb[0], rgb[1], rgb[2]);
	if (!mid || !*mid)
		printf("0x%06x", color);
	else
		printf("%s", mid);
	printf(KDEF "%s", post);
}

void	print_vector(char *message, t_vector vec)
{
	printf("%s", message);
	printf("%.1f,%.1f,%-8.1f", vec[0], vec[1], vec[2]);
}
