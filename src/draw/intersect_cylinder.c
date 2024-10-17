/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:16:50 by akretov           #+#    #+#             */
/*   Updated: 2024/10/17 16:15:45 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_cyl_sides(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_quadratic	eq;
	t_vec3		oc;

	vec3_a_to_b(oc, *ray->origin, cylinder->center);
	// Calculate the coefficients of the quadratic equation
	float d_dot_axis = dot_product(ray->udir, cylinder->axis);
	float oc_dot_axis = dot_product(oc, cylinder->axis);

	eq.a = 1 - d_dot_axis * d_dot_axis;
	eq.b = 2 * (d_dot_axis * oc_dot_axis -dot_product(oc, ray->udir) );
	eq.c = dot_product(oc, oc) - oc_dot_axis * oc_dot_axis - cylinder->radius * cylinder->radius;

	// Calculate discriminant
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (-1);  // No intersection

	/*float sqrt_discriminant = sqrt(eq.discriminant);*/
	float t1 = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);

	t_vec3 intersection_point;

	// Check the first intersection
	if (t1 > EPSILON && t1 < *t)
	{
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t1);
		float height_at_t1 = dot_product(cylinder->axis, intersection_point) - dot_product(cylinder->axis, cylinder->center);
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

int intersect_cyl_caps(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_vec3	top_cap_center;
	t_vec3	bottom_cap_center;
	float	closest_t;
	int		closest_cap;
	float	denom_top;
	float	t_top;
	float	denom_bottom;
	float	t_bottom;

	vec3_scale_add(top_cap_center, cylinder->center, cylinder->axis, cylinder->height);
	vec3_scale_add(bottom_cap_center, cylinder->center, cylinder->axis, 0);
	closest_t = *t;
	closest_cap = 0;
	denom_top = dot_product(ray->udir, cylinder->axis);
	t_top = FLT_MAX;  // Set an initial large value for t_top
	if (fabs(denom_top) > EPSILON) // Ensure the ray is not parallel to the cap
	{
		t_top = (dot_product(cylinder->axis, top_cap_center) - dot_product(cylinder->axis, *ray->origin)) / denom_top;
		if (t_top > EPSILON && t_top < closest_t)
		{
			t_vec3 intersection_point;
			vec3_scale_add(intersection_point, *ray->origin, ray->udir, t_top);
			t_vec3 point_to_center;
			vec3_a_to_b(point_to_center, top_cap_center, intersection_point);
			if (vec3_length(point_to_center) <= cylinder->radius)  // Check if within the cap radius
				{
					closest_t = t_top;
					closest_cap = 1;  // Indicate that top cap is the closest so far
				}
			}
		}
	denom_bottom = dot_product(ray->udir, cylinder->axis);
	t_bottom = FLT_MAX;  // Set an initial large value for t_bottom
	if (fabs(denom_bottom) > EPSILON) // Ensure the ray is not parallel to the cap
	{
		t_bottom = (dot_product(cylinder->axis, bottom_cap_center) - dot_product(cylinder->axis, *ray->origin)) / denom_bottom;
		if (t_bottom > EPSILON && t_bottom < closest_t)
		{
			t_vec3 intersection_point;
			vec3_scale_add(intersection_point, *ray->origin, ray->udir, t_bottom);
			t_vec3 point_to_center;
			vec3_a_to_b(point_to_center, bottom_cap_center, intersection_point);
			if (vec3_length(point_to_center) <= cylinder->radius)  // Check if within the cap radius
			{
				closest_t = t_bottom;
				closest_cap = 2;  // Indicate that bottom cap is the closest so far
			}
		}
	}

	if (closest_cap != 0)  // If a valid cap intersection was found
	{
		*t = closest_t;
		ray->obj_type = SEL_CYLINDER_CAP;
		ray->object = cylinder;
		return (cylinder->color);  // Return the color of the cylinder cap
	}
	return (-1);
}

int intersect_cylinder(t_cylinder *cylinder, t_ray *ray, float *t)
{
	int color;

	color = intersect_cyl_sides(cylinder, ray, t);
	if (color != -1)
		return (color);
	color = intersect_cyl_caps(cylinder, ray, t);
	if (color != -1)
		return (color);
	return (-1);
}

void intersect_cylinders(t_scene *scene, t_ray *ray, float *t, int *col)
{
	int		temp_color;
	int		pixel_color;
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
			*col = temp_color;
		}
		temp_color = -1;
	}
}
