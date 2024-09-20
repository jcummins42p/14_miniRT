/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uniqs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:47:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 15:55:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_ambient(t_ambient ambient)
{
	printf("->Ambient:\n");
	printf("\tluminosity:\t%.2f", ambient.lum);
	print_color("\t\t\thue:\t\t", "", "\n", ambient.hue);
}

void	print_camera(t_camera camera)
{
	printf("->Camera:\n");
	print_vector("\tviewpoint:\t", camera.point);
	print_vector("\torientation:\t", camera.dir);
	printf("\t\tfov:\t%d\n", camera.fov);
}

void	print_light(t_light light)
{
	printf("->Light:\n");
	print_vector("\tpoint:\t\t", light.point);
	printf("\tbrightness:\t%.2f", light.lum);
	print_color("\t\t\thue:\t", "", "\n", light.hue);
}

void	print_uniqs(t_scene	*scene)
{
	print_ambient(scene->amb);
	print_camera(scene->cam);
	print_light(scene->light);
}
