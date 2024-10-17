/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:16:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:10:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	gets the normal at a given bounce point on the cylinder curved surface
void	get_cylinder_normal(t_vec3 normal, t_cylinder *cylinder, t_ray *ray)
{
	float	proj_len;
	t_vec3	point_on_axis;
	t_vec3	intersection_to_center;

	vec3_a_to_b(intersection_to_center, cylinder->center, ray->bounce);
	proj_len = dot_product(intersection_to_center, cylinder->axis);
	vec3_scale_add(point_on_axis, cylinder->center, cylinder->axis, proj_len);
	vec3_a_to_b(normal, point_on_axis, ray->bounce);
	vec3_normalize(normal, normal);
}

//	R = L - 2(L.N)N
//	results in a unit vector showing the reflection direction
void	vec3_surface_reflection(t_vec3 reflect, t_vec3 light, t_vec3 norm)
{
	t_vec3	light_u;
	float	dot_ln;

	vec3_normalize(light_u, light);
	dot_ln = dot_product(light, norm);
	vec3_scaleize(reflect, norm, 2 * dot_ln);
	vec3_a_to_b(reflect, light_u, reflect);
	vec3_normalize(reflect, reflect);
}
