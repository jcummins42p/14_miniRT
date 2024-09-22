/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:00:19 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/22 12:15:17 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	aa_bound_sphere(t_sphere *sphere)
{
	sphere->bounds.max[0] = sphere->center[0] + sphere->diamtr / 2;
	sphere->bounds.max[1] = sphere->center[1] + sphere->diamtr / 2;
	sphere->bounds.max[2] = sphere->center[2] + sphere->diamtr / 2;
	sphere->bounds.min[0] = sphere->center[0] - sphere->diamtr / 2;
	sphere->bounds.min[1] = sphere->center[1] - sphere->diamtr / 2;
	sphere->bounds.min[2] = sphere->center[2] - sphere->diamtr / 2;
}

void	aa_bound_capsule(t_cylinder *cylinder)
{
	(void) cylinder;
}

void	set_aa_bounding_boxes(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->n_spheres)
		aa_bound_sphere(&scene->sphs[i++]);
	i = 0;
	while (i < scene->n_cylinders)
		aa_bound_capsule(&scene->cyls[i++]);
}
