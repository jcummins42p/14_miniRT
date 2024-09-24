/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:55:57 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 20:56:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	color_int_to_vector(t_rgb rgb, t_color color)
{
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color) & 0xFF;
}

int	color_vector_to_int(t_rgb rgb)
{
	int		color;

	color = 0;
	color += rgb[0] << 16;
	color += rgb[1] << 8;
	color += rgb[2];
	return (color);
}

//	shifts 'original' to 'target' by a ratio: 0 is all original, 1 is all target
t_color	color_gradient(t_color original, t_color target, float ratio)
{
	t_rgb	ori;
	t_rgb	end;
	t_rgb	out;

	if (ratio < 0)
		return (original);
	if (ratio > 1)
		return (target);
	color_int_to_vector(ori, original);
	color_int_to_vector(end, target);
	out[0] = fmin(fmax(0, (ori[0] + (int)((end[0] - ori[0]) * ratio))), 255);
	out[1] = fmin(fmax(0, (ori[1] + (int)((end[1] - ori[1]) * ratio))), 255);
	out[2] = fmin(fmax(0, (ori[2] + (int)((end[2] - ori[2]) * ratio))), 255);

	return (color_vector_to_int(out));
}
