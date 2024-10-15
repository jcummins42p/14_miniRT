/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:55:57 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/15 09:38:11 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	color_int_to_vector(t_rgb rgb, int color)
{
	rgb[_R] = (color >> 16) & 0xFF;
	rgb[_G] = (color >> 8) & 0xFF;
	rgb[_B] = (color) & 0xFF;
}

int	color_vector_to_int(t_rgb rgb)
{
	int		color;

	color = 0;
	color += rgb[_R] << 16;
	color += rgb[_G] << 8;
	color += rgb[_B];
	return (color);
}

int color_invert(int original)
{
	t_rgb	ori;
	t_rgb	inv;

	color_int_to_vector(ori, original);
	inv[_R] = 255 - ori[_R];
	inv[_G] = 255 - ori[_G];
	inv[_B] = 255 - ori[_B];
	return (color_vector_to_int(inv));
}

//	for direct light illuminating a color?
int	color_illuminate(int original, int target, float ratio)
{
	t_rgb	ori;
	t_rgb	end;
	t_rgb	out;

	if (ratio < 0)
		return (0x000000);
	if (ratio > 1)
		return (ratio = 1);
	color_int_to_vector(ori, original);
	color_int_to_vector(end, target);
	out[_R] = fmin(fmax(0, (ori[0] * (int)((end[_R] / 255) * ratio))), 255);
	out[_G] = fmin(fmax(0, (ori[1] * (int)((end[_G] / 255) * ratio))), 255);
	out[_B] = fmin(fmax(0, (ori[2] * (int)((end[_B] / 255) * ratio))), 255);

	return (color_vector_to_int(out));
}

int	color_subtract(int original, int target, float ratio)
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
	out[_R] = fmin(fmax(0, (ori[0] - (int)(end[_R] * ratio))), 255);
	out[_G] = fmin(fmax(0, (ori[1] - (int)(end[_G] * ratio))), 255);
	out[_B] = fmin(fmax(0, (ori[2] - (int)(end[_B] * ratio))), 255);

	return (color_vector_to_int(out));
}

int	color_addition(int original, int target)
{
	t_rgb	ori;
	t_rgb	end;
	t_rgb	out;

	color_int_to_vector(ori, original);
	color_int_to_vector(end, target);
	out[_R] = fmin(fmax(0, (ori[_R] + end[_R])), 255);
	out[_G] = fmin(fmax(0, (ori[_G] + end[_G])), 255);
	out[_B] = fmin(fmax(0, (ori[_B] + end[_B])), 255);

	return (color_vector_to_int(out));
}

//	shifts 'original' to 'target' by a ratio: 0 is all original, 1 is all target
int	color_shift(int original, int target, float ratio)
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
	out[_R] = fmin(fmax(0, (ori[0] + (int)((end[_R] - ori[_R]) * ratio))), 255);
	out[_G] = fmin(fmax(0, (ori[1] + (int)((end[_G] - ori[_G]) * ratio))), 255);
	out[_B] = fmin(fmax(0, (ori[2] + (int)((end[_B] - ori[_B]) * ratio))), 255);

	return (color_vector_to_int(out));
}
