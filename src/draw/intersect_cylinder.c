/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:16:50 by akretov           #+#    #+#             */
/*   Updated: 2024/10/04 14:04:34 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void calculate_coefficients(t_cylinder *cyl, t_ray *ray, t_vec3 cam_to_cyl_cent, float *abc)
{
	abc[0] = dot_product(ray->udir, ray->udir) - pow(dot_product(ray->udir, cyl->axis), 2);
	abc[1] = 2.0 * (dot_product(cam_to_cyl_cent, ray->udir)
				- dot_product(cam_to_cyl_cent, cyl->axis)
				* dot_product(ray->udir, cyl->axis));
	abc[2] = dot_product(cam_to_cyl_cent, cam_to_cyl_cent)
				- pow(dot_product(cam_to_cyl_cent, cyl->axis), 2)
				- pow(cyl->diamtr / 2.0, 2);
}

float solve_quadratic(float a, float b, float discriminant)
{
	float sqrt_d;
	float t0;
	float t1;

	sqrt_d = sqrt(discriminant);
	t0 = (-b - sqrt_d) / (2.0 * a);
	t1 = (-b + sqrt_d) / (2.0 * a);
	if (t0 > EPSILON && t1 > EPSILON)
	{
		if (t0 < t1)
			return t0;
		return t1;
	}
	else if (t0 > EPSILON)
		return t0;
	else if (t1 > EPSILON)
		return t1;
	return (-1);
}

t_color intersect_cylinder(t_cylinder *cyl, t_ray *ray, float *t)
{
	float abc[3];
	float discriminant;
	float temp_t;
	t_vec3 cam_to_cyl_cent;

	vec3_a_to_b(cam_to_cyl_cent, *ray->origin, cyl->center);
	calculate_coefficients(cyl, ray, cam_to_cyl_cent, abc);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (-1);
	temp_t = solve_quadratic(abc[0], abc[1], discriminant);
	if (temp_t > 0 && temp_t < *t)
	{
		*t = temp_t;
		ray->object_type = SEL_CYLINDER;
		ray->object = cyl;
		return (cyl->color);
	}
	return (-1);
}

t_color intersect_cylinders(t_scene *scene, t_ray *ray, float *t)
{
	t_color pixel_color;
	t_color temp_color;
	float temp_t;
	int i;

	i = -1;
	pixel_color = -1;
	temp_t = *t;
	while (++i < scene->n_cylinders)
	{
		temp_color = intersect_cylinder(&scene->cyls[i], ray, &temp_t);
		if (temp_color >= 0 && temp_t < *t)
		{
			pixel_color = temp_color;
			if (ray->origin == &scene->cam.point)
			{
				scene->screen_object[ray->y][ray->x] = &scene->cyls[i];
				scene->select_type[ray->y][ray->x] = SEL_CYLINDER;
			}
			*t = temp_t;
		}
	}
	return (pixel_color);
}
