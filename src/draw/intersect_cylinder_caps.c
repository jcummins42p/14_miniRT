/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_caps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:37:47 by akretov           #+#    #+#             */
/*   Updated: 2024/10/17 16:46:35 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_cap_intersection(t_vec3 cap_center, t_ray *ray, 
								t_cylinder *cylinder, float *t, float denom)
{
	t_vec3	intersection_point;
	t_vec3	point_to_center;
	float	t_cap;

	t_cap = (dot_product(cylinder->axis, cap_center) - 
			dot_product(cylinder->axis, *ray->origin)) / denom;
	if (t_cap > EPSILON && t_cap < *t)
	{
		vec3_scale_add(intersection_point, *ray->origin, ray->udir, t_cap);
		vec3_a_to_b(point_to_center, cap_center, intersection_point);
		if (vec3_length(point_to_center) <= cylinder->radius)
		{
			*t = t_cap;
			return (1);
		}
	}
	return (0);
}

int	intersect_cyl_caps(t_cylinder *cylinder, t_ray *ray, float *t)
{
	t_vec3	top_cap_center;
	t_vec3	bottom_cap_center;
	float	closest_t;
	int		closest_cap;
	float	denom;

	vec3_scale_add(top_cap_center, cylinder->center, cylinder->axis, 
					cylinder->height);
	vec3_scale_add(bottom_cap_center, cylinder->center, cylinder->axis, 0);
	closest_t = *t;
	closest_cap = 0;
	denom = dot_product(ray->udir, cylinder->axis);
	if (fabs(denom) > EPSILON)
	{
		if (check_cap_intersection(top_cap_center, ray, cylinder, 
									&closest_t, denom))
			closest_cap = 1;
		if (check_cap_intersection(bottom_cap_center, ray, cylinder, 
									&closest_t, denom))
			closest_cap = 2;
	}
	if (closest_cap != 0)
	{
		*t = closest_t;
		ray->obj_type = SEL_CYLINDER_CAP;
		ray->object = cylinder;
		return (cylinder->color);
	}
	return (-1);
}
