/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:35:07 by akretov           #+#    #+#             */
/*   Updated: 2024/10/18 16:54:17 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cacl_quad(t_cylinder *cylinder, t_ray *ray, t_quadratic	*eq)
{
	t_vec3	oc;
	float	d_dot_axis;
	float	oc_dot_ax;

	vec3_a_to_b(oc, *ray->origin, cylinder->center);
	d_dot_axis = dot_product(ray->udir, cylinder->axis);
	oc_dot_ax = dot_product(oc, cylinder->axis);
	eq->a = 1 - d_dot_axis * d_dot_axis;
	eq->b = 2 * (d_dot_axis * oc_dot_ax - dot_product(oc, ray->udir));
	eq->c = dot_product(oc, oc) - oc_dot_ax * oc_dot_ax
		- cylinder->radius * cylinder->radius;
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (eq->discriminant < 0)
		return (-1);
	return (0);
}
