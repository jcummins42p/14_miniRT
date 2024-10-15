/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shaders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:40:08 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/15 11:09:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	darkens pixel towards black if it is further away from the camera
int	shade_pixel_distance(int pixel_color, float distance)
{
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift(pixel_color, 0x000000, (DARK * log(distance / (BRIGHT * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

int	shade_light_distance(int pixel_color, float distance, float lum)
{
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift(pixel_color, 0x000000, ((1 - lum) * DARK * log(distance * distance / (2 * BRIGHT * lum * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

//	creates single combined light value from directional and ambient lights
int	combine_lights(int light_color, t_ambient amb)
{
	int	amb_color;

	amb_color = color_shift(amb.hue, 0x000000, 1 - amb.lum);
	return (color_addition(light_color, amb_color));
}

//	applies the combined light value from the above function to the material
//	color.
int	illuminate_pixel(int pixel_color, int light_color)
{
	return (color_subtract(pixel_color, color_invert(light_color), 1));
}

//	versions of the same functions using unions instead of integers

t_col	shade_pixel_distance_u(t_col pixel_color, float distance)
{
	t_col	black;

	black.i = 0;
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift_u(pixel_color, black, (DARK * log(distance / (BRIGHT * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

t_col	shade_light_distance_u(t_col pixel_color, float distance, float lum)
{
	t_col	black;

	black.i = 0;
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift_u(pixel_color, black, ((1 - lum) * DARK * log(distance * distance / (2 * BRIGHT * lum * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

//	creates single combined light value from directional and ambient lights
t_col	combine_lights_u(t_col light_color, t_ambient amb)
{
	t_col	amb_color;
	t_col	black;

	black.i = 0;
	amb_color.i = amb.hue;
	amb_color = color_shift_u(amb_color, black, 1 - amb.lum);
	return (color_addition_u(light_color, amb_color));
}

//	applies the combined light value from the above function to the material
//	color.
t_col	illuminate_pixel_u(t_col pixel_color, t_col light_color)
{
	return (color_subtract_u(pixel_color, color_invert_u(light_color), 1));
}
