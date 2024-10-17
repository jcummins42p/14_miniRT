/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:12:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Scale the direction vector by the given magnitude
void	vec3_scale_add(t_vec3 dest, t_vec3 base, t_vec3 direction, float magnitude)
{
	t_vec3	scaled_direction;

	vec3_scaleize(scaled_direction, direction, magnitude);
	dest[_X] = base[_X] + scaled_direction[_X];
	dest[_Y] = base[_Y] + scaled_direction[_Y];
	dest[_Z] = base[_Z] + scaled_direction[_Z];
}

void	vec3_set_a(t_vec3 a, t_vec3 b)
{
	a[_X] = b[_X];
	a[_Y] = b[_Y];
	a[_Z] = b[_Z];
}

void	vec3_position(t_vec3 dest, t_vec3 origin, t_vec3 unit, float magnitude)
{
	dest[_X] = origin[_X] + (unit[_X] * magnitude);
	dest[_Y] = origin[_Y] + (unit[_Y] * magnitude);
	dest[_Z] = origin[_Z] + (unit[_Z] * magnitude);
}

void	vec3_a_to_b(t_vec3 dir_out, t_vec3 point_a, t_vec3 point_b)
{
	dir_out[_X] = point_b[_X] - point_a[_X];
	dir_out[_Y] = point_b[_Y] - point_a[_Y];
	dir_out[_Z] = point_b[_Z] - point_a[_Z];
}

void	vec3_scaleize(t_vec3 scalar, t_vec3 unit, float magnitude)
{
	scalar[_X] = unit[_X] * magnitude;
	scalar[_Y] = unit[_Y] * magnitude;
	scalar[_Z] = unit[_Z] * magnitude;
}
//	stores the unit vector of 'direction' in 'unit'
void	vec3_normalize(t_vec3 unit, t_vec3 direction)
{
	float		v_len;

	v_len = vec3_length(direction);
	if (v_len != 0)
	{
		unit[_X] = direction[_X] / v_len;
		unit[_Y] = direction[_Y] / v_len;
		unit[_Z] = direction[_Z] / v_len;
	}
}
