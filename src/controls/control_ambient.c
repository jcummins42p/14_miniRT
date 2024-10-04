/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:03:37 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/04 13:45:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	color_alter_vector(t_rgb color, int component, float amount)
{
	if (component < _R || component > _B)
		return ;
	color[component] = color[component] + amount;
	if (color[component] < 0)
		color[component] = 0;
	else if (color[component] > 255)
		color[component] = 255;
}

void	k_control_ambient(int keysym, t_scene *scene)
{
	t_ambient	*ambient;
	t_rgb		temp_color;

	ambient = &scene->amb;
	color_int_to_vector(temp_color, ambient->hue);
	if (keysym == XK_KP_7)
		color_alter_vector(temp_color, _R, 10);
	else if (keysym == XK_KP_1)
		color_alter_vector(temp_color, _R, -10);
	else if (keysym == XK_KP_8)
		color_alter_vector(temp_color, _G, 10);
	else if (keysym == XK_KP_2)
		color_alter_vector(temp_color, _G, -10);
	else if (keysym == XK_KP_9)
		color_alter_vector(temp_color, _B, 10);
	else if (keysym == XK_KP_3)
		color_alter_vector(temp_color, _B, -10);
	else if (keysym == XK_KP_4)
		ambient->lum -= 0.1;
	else if (keysym == XK_KP_6)
		ambient->lum += 0.1;
	if (ambient->lum > 1)
		ambient->lum = 1;
	if (ambient->lum < 0)
		ambient->lum = 0;
	ambient->hue = color_vector_to_int(temp_color);
}

void	k_control_light(int keysym, t_scene *scene)
{
	t_light	*light;
	t_rgb	temp_color;

	light = &scene->light;
	color_int_to_vector(temp_color, light->hue);
	if (keysym == XK_KP_7)
		color_alter_vector(temp_color, _R, 10);
	else if (keysym == XK_KP_1)
		color_alter_vector(temp_color, _R, -10);
	else if (keysym == XK_KP_8)
		color_alter_vector(temp_color, _G, 10);
	else if (keysym == XK_KP_2)
		color_alter_vector(temp_color, _G, -10);
	else if (keysym == XK_KP_9)
		color_alter_vector(temp_color, _B, 10);
	else if (keysym == XK_KP_3)
		color_alter_vector(temp_color, _B, -10);
	else if (keysym == XK_KP_4)
		light->lum -= 0.1;
	else if (keysym == XK_KP_6)
		light->lum += 0.1;
	if (light->lum > 1)
		light->lum = 1;
	if (light->lum < 0)
		light->lum = 0;
	light->hue = color_vector_to_int(temp_color);
}
