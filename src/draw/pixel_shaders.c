/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shaders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:40:08 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/07 18:06:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	darkens pixel towards black if it is further away from the camera
int	shade_pixel_distance(t_color pixel_color, float distance)
{
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift(pixel_color, 0x000000, (DARK * log(distance / (BRIGHT * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

int	shade_light_distance(t_color pixel_color, float distance, float lum)
{
	/*return (color_shift(pixel_color, 0x000000, distance / 150));*/
	return (color_shift(pixel_color, 0x000000, ((1 - lum) * DARK * log(distance * distance / (2 * BRIGHT * lum * 2)))));
	/*return (color_shift(pixel_color, 0x000000, (1 / (distance * distance))));*/
}

//	creates single combined light value from directional and ambient lights
int	combine_lights(t_color light_color, t_ambient amb)
{
	t_color	amb_color;

	amb_color = color_shift(amb.hue, 0x000000, 1 - amb.lum);
	return (color_addition(light_color, amb_color));
}

//	applies the combined light value from the above function to the material
//	color.
int	illuminate_pixel(t_color pixel_color, t_color light_color)
{
	return (color_subtract(pixel_color, color_invert(light_color), 1));
}

