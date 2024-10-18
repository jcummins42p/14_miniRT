/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:03:37 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 15:35:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	color_alter_vector(t_rgb color, int component, float amount)
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
	t_rgb		temp_color;

	color_int_to_vector(temp_color, scene->amb.hue);
	if (keysym == XK_KP_7)
		color_alter_vector(temp_color, _R, 25);
	else if (keysym == XK_KP_1)
		color_alter_vector(temp_color, _R, -25);
	else if (keysym == XK_KP_8)
		color_alter_vector(temp_color, _G, 25);
	else if (keysym == XK_KP_2)
		color_alter_vector(temp_color, _G, -25);
	else if (keysym == XK_KP_9)
		color_alter_vector(temp_color, _B, 25);
	else if (keysym == XK_KP_3)
		color_alter_vector(temp_color, _B, -25);
	else if (keysym == XK_KP_4)
		scene->amb.lum -= 0.1;
	else if (keysym == XK_KP_6)
		scene->amb.lum += 0.1;
	if (scene->amb.lum > 1)
		scene->amb.lum = 1;
	if (scene->amb.lum < 0)
		scene->amb.lum = 0;
	scene->amb.hue = color_vector_to_int(temp_color);
}

void	k_control_light(int keysym, t_scene *scene)
{
	t_rgb	temp_color;

	color_int_to_vector(temp_color, scene->light.hue);
	if (keysym == XK_KP_7)
		color_alter_vector(temp_color, _R, 25);
	else if (keysym == XK_KP_1)
		color_alter_vector(temp_color, _R, -25);
	else if (keysym == XK_KP_8)
		color_alter_vector(temp_color, _G, 25);
	else if (keysym == XK_KP_2)
		color_alter_vector(temp_color, _G, -25);
	else if (keysym == XK_KP_9)
		color_alter_vector(temp_color, _B, 25);
	else if (keysym == XK_KP_3)
		color_alter_vector(temp_color, _B, -25);
	else if (keysym == XK_KP_4)
		scene->light.lum -= 0.1;
	else if (keysym == XK_KP_6)
		scene->light.lum += 0.1;
	if (scene->light.lum > 1)
		scene->light.lum = 1;
	if (scene->light.lum < 0)
		scene->light.lum = 0;
	scene->light.hue = color_vector_to_int(temp_color);
}
