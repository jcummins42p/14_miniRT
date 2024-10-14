/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:16:50 by akretov           #+#    #+#             */
/*   Updated: 2024/10/14 20:18:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_cylinder_sides(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_quadratic	eq;
	t_vec3		oc;

	vec3_a_to_b(oc, *ray->origin, cylinder->center);
	// Calculate the coefficients of the quadratic equation
	float d_dot_axis = dot_product(ray->udir, cylinder->axis);
	float oc_dot_axis = dot_product(oc, cylinder->axis);

	float radius = cylinder->diamtr / 2;
	eq.a = 1 - d_dot_axis * d_dot_axis;
	eq.b = 2 * (d_dot_axis * oc_dot_axis -dot_product(oc, ray->udir) );
	eq.c = dot_product(oc, oc) - oc_dot_axis * oc_dot_axis - radius * radius;

	// Calculate discriminant
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (-1);  // No intersection

	float sqrt_discriminant = sqrt(eq.discriminant);
	float t1 = (-eq.b - sqrt_discriminant) / (2 * eq.a);

	t_vec3 intersection_point;

	// Check the first intersection
	if (t1 > EPSILON && t1 < *t)
	{
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t1);
		float height_at_t1 = dot_product(cylinder->axis, intersection_point) - dot_product(cylinder->axis, cylinder->center);
		if (height_at_t1 >= 0 && height_at_t1 <= cylinder->height)
		{
			*t = t1;
			ray->object_type = SEL_CYLINDER_SIDE;
			ray->object = cylinder;
			return (cylinder->color);
		}
	}

	return (-1);
}

int intersect_cylinder_caps(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_vec3	top_cap_center;
	t_vec3	bottom_cap_center;
	t_vec3	intersection_point;

	float radius = cylinder->diamtr / 2;

	// Calculate the centers of the top and bottom caps
	vec3_scale_add(top_cap_center, cylinder->center, cylinder->axis, cylinder->height);
	vec3_scale_add(bottom_cap_center, cylinder->center, cylinder->axis, 0);

	// Check intersection with the top cap (plane)
	float denom_top = dot_product(ray->udir, cylinder->axis);
	if (fabs(denom_top) > EPSILON) // Ensure the ray is not parallel to the cap
	{
		float t_top = (dot_product(cylinder->axis, top_cap_center) - dot_product(cylinder->axis, *ray->origin)) / denom_top;
		if (t_top > EPSILON && t_top < *t)
		{
			vec3_scale_add(intersection_point, *ray->origin, ray->udir, t_top);
			t_vec3 point_to_center;
			vec3_a_to_b(point_to_center, top_cap_center, intersection_point);
			if (vec3_length(point_to_center) <= radius)  // Check if within the cap radius
			{
				*t = t_top;
				ray->object_type = SEL_CYLINDER_CAP;
				ray->object = cylinder;
				return (cylinder->color);
			}
		}
	}

	// Check intersection with the bottom cap (plane)
	float denom_bottom = dot_product(ray->udir, cylinder->axis);
	if (fabs(denom_bottom) > EPSILON) // Ensure the ray is not parallel to the cap
	{
		float t_bottom = (dot_product(cylinder->axis, bottom_cap_center) - dot_product(cylinder->axis, *ray->origin)) / denom_bottom;
		if (t_bottom > EPSILON && t_bottom < *t)
		{
			vec3_scale_add(intersection_point, *ray->origin, ray->udir, t_bottom);
			t_vec3 point_to_center;
			vec3_a_to_b(point_to_center, bottom_cap_center, intersection_point);
			if (vec3_length(point_to_center) <= radius)  // Check if within the cap radius
			{
				*t = t_bottom;
				ray->object_type = SEL_CYLINDER_CAP;
				ray->object = cylinder;
				return (cylinder->color);
			}
		}
	}
	return (-1);
}

int intersect_cylinder(t_cylinder *cylinder, t_ray *ray, float *t)
{
	int color;

	color = intersect_cylinder_sides(cylinder, ray, t);
	if (color != -1)
		return (color);
	color = intersect_cylinder_caps(cylinder, ray, t);
	if (color != -1)
		return (color);
	return (-1);
}

int intersect_cylinders(t_scene *scene, t_ray *ray, float *t)
{
	int	temp_color;
	int	pixel_color;
	float	temp_t;
	int		i;

	i = -1;
	temp_color = -1;
	pixel_color = -1;
	temp_t = *t;
	while (++i < scene->n_cylinders)
	{
		temp_color = intersect_cylinder(&scene->cyls[i], ray, &temp_t);
		if ((temp_color >= 0) && temp_t < *t)
		{
			pixel_color = temp_color;
			if (ray->origin == &scene->cam.point)
			{
				scene->screen_object[ray->y][ray->x] = &scene->cyls[i]; 
				scene->select_type[ray->y][ray->x] = SEL_CYLINDER_SIDE;
			}
			*t = temp_t;
		}
		temp_color = -1;
	}
	return (pixel_color);
}
