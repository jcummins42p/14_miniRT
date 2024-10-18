/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:16:50 by akretov           #+#    #+#             */
/*   Updated: 2024/10/18 14:15:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_cyl_sides(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_quadratic	eq;
	float		t1;
	t_vec3		intersection_point;
	float		height_at_t1;

	if (calculate_quadratic(cylinder, ray, &eq))
		return (-1);
	t1 = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	if (t1 > EPSILON && t1 < *t)
	{
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t1);
		height_at_t1 = dot_product(cylinder->axis, intersection_point)
			- dot_product(cylinder->axis, cylinder->center);
		if (height_at_t1 >= 0 && height_at_t1 <= cylinder->height)
		{
			*t = t1;
			ray->obj_type = SEL_CYLINDER_SIDE;
			ray->object = cylinder;
			return (cylinder->color);
		}
	}
	return (-1);
}

int	intersect_cylinder(t_cylinder *cylinder, t_ray *ray, float *t)
{
	int	color;

	color = intersect_cyl_sides(cylinder, ray, t);
	if (color != -1)
		return (color);
	color = intersect_cyl_caps(cylinder, ray, t);
	if (color != -1)
		return (color);
	return (-1);
}

void	intersect_cylinders(t_scene *scene, t_ray *ray, float *t, int *col)
{
	int		temp_color;
	float	temp_t;
	int		i;

	i = -1;
	temp_color = -1;
	temp_t = *t;
	while (++i < scene->n_cylinders)
	{
		temp_color = intersect_cylinder(&scene->cyls[i], ray, &temp_t);
		if ((temp_color >= 0) && temp_t < *t)
		{
			if (ray->origin == &scene->cam.point)
			{
				scene->screen_object[ray->y][ray->x] = &scene->cyls[i];
				scene->select_type[ray->y][ray->x] = SEL_CYLINDER_SIDE;
			}
			*t = temp_t;
			*col = temp_color;
		}
		temp_color = -1;
	}
}
