/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:57:27 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/11 18:41:26 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_color(char *pre, char *mid, char *post, int color)
{
	int	rgb[3];

	if (!pre || !mid || ! post)
		return ;
	rgb[_R] = (color >> 16) & 0xFF;
	rgb[_G] = (color >> 8) & 0xFF;
	rgb[_B] = color & 0xFF;
	printf(KDEF "%s", pre);
	printf("\033[38;2;%d;%d;%dm", rgb[_R], rgb[_G], rgb[_B]);
	if (!mid || !*mid)
		printf("0x%06x", color);
	else
		printf("%s", mid);
	printf(KDEF "%s", post);
}

void	print_vec3(char *message, t_vec3 vec)
{
	printf("%s", message);
	printf("%.1f,%.1f,%-8.1f", vec[_X], vec[_Y], vec[_Z]);
}
