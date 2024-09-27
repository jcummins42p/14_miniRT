/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/27 15:49:44 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

float	vec3_length(t_vec3 vec)
{
	return (sqrtf((vec[_X] * vec[_X])
			+ (vec[_Y] * vec[_Y])
			+ (vec[_Z] * vec[_Z])));
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
