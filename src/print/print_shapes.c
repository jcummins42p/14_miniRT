/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:59:15 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 15:23:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_sphere(t_sphere sphere)
{
	printf("  Sph.%-2d:", sphere.id);
	print_vec3(" center: ", sphere.center);
	printf("\tdiameter: %9.2f", sphere.diamtr);
	print_color("\tcolor: ", "", "\n", sphere.color);
}

void	print_plane(t_plane plane)
{
	printf("  Pln.%-2d:", plane.id);
	print_vec3(" anchor: ", plane.anch);
	print_vec3("\tnorm: ", plane.norm);
	print_color("\tcolor: ", "", "\n", plane.color);
}

void	print_cylinder(t_cylinder cylinder)
{
	printf("  Cyl.%-2d:", cylinder.id);
	print_vec3(" center: ", cylinder.center);
	print_vec3("\taxis: ", cylinder.axis);
	printf("\tdiameter: %.2f", cylinder.diamtr);
	printf("\theight: %.2f", cylinder.height);
	print_color("\tcolor: ", "", "\n", cylinder.color);
}

void	print_shapes(t_scene *scene)
{
	int	i;

	i = 0;
	printf("->Spheres:\n");
	while (i < scene->n_spheres)
		print_sphere(scene->sphs[i++]);
	i = 0;
	printf("->Planes:\n");
	while (i < scene->n_planes)
		print_plane(scene->plns[i++]);
	i = 0;
	printf("->Cylinders:\n");
	while (i < scene->n_cylinders)
		print_cylinder(scene->cyls[i++]);
}
