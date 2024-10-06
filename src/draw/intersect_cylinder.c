/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:16:50 by akretov           #+#    #+#             */
/*   Updated: 2024/10/06 17:28:54 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Function to calculate coefficients for cylinder intersection
void vec3_scale_add(t_vec3 dest, t_vec3 base, t_vec3 direction, float magnitude)
{
	// Scale the direction vector by the given magnitude
	t_vec3 scaled_direction;
	vec3_scaleize(scaled_direction, direction, magnitude);

	// Add the scaled direction to the base vector
	dest[_X] = base[_X] + scaled_direction[_X];
	dest[_Y] = base[_Y] + scaled_direction[_Y];
	dest[_Z] = base[_Z] + scaled_direction[_Z];
}

t_color intersect_cylinder(t_cylinder *cylinder, t_ray *ray, float *t) {
	t_quadratic eq;
	t_vec3 oc;

	// Vector from ray origin to cylinder center
	vec3_a_to_b(oc, *ray->origin, cylinder->center);

	// Calculate the coefficients of the quadratic equation
	float d_dot_axis = dot_product(ray->udir, cylinder->axis);
	float oc_dot_axis = dot_product(oc, cylinder->axis);
		
	float radius = cylinder->diamtr / 2;
	eq.a = dot_product(ray->udir, ray->udir) - d_dot_axis * d_dot_axis;
	eq.b = 2 * (dot_product(oc, ray->udir) - d_dot_axis * oc_dot_axis);
	eq.c = dot_product(oc, oc) - oc_dot_axis * oc_dot_axis - radius * radius;

	// Calculate discriminant
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;

	if (eq.discriminant < 0)
		return (-1); // No intersection

	// Calculate both potential intersection points (t1 and t2)
	float sqrt_discriminant = sqrt(eq.discriminant);
	float t1 = 0 -(-eq.b - sqrt_discriminant) / (2 * eq.a);
	float t2 = 0 -(-eq.b + sqrt_discriminant) / (2 * eq.a);

	// Check for first intersection
	if (t1 > EPSILON && t1 < *t) {
		// Calculate intersection point
		t_vec3 intersection_point;
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t1);

		// Check if within cylinder's height
		float height_at_t1 = dot_product(cylinder->axis, intersection_point) - dot_product(cylinder->axis, cylinder->center);
		if (height_at_t1 >= 0 && height_at_t1 <= cylinder->height) {
			*t = t1;
			ray->object_type = SEL_CYLINDER;
			ray->object = cylinder;
			return (cylinder->color);
		}
	}

	// Check for second intersection
	if (t2 > EPSILON && t2 < *t) {
		// Calculate intersection point
		t_vec3 intersection_point;
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t2);

		// Check if within cylinder's height
		float height_at_t2 = dot_product(cylinder->axis, intersection_point) - dot_product(cylinder->axis, cylinder->center);
		if (height_at_t2 >= 0 && height_at_t2 <= cylinder->height) {
			*t = t2;
			ray->object_type = SEL_CYLINDER;
			ray->object = cylinder;
			return (cylinder->color);
		}
	}

    return (-1); // No valid intersection
}

t_color	intersect_cylinders(t_scene *scene, t_ray *ray, float *t)
{
	t_color	temp_color;
	t_color	pixel_color;
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
				scene->screen_object[ray->y][ray->x] = &scene->sphs[i];
				scene->select_type[ray->y][ray->x] = SEL_CYLINDER;
			}
			*t = temp_t;
		}
		temp_color = -1;
	}
	return (pixel_color);
}
