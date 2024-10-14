/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:09:56 by akretov           #+#    #+#             */
/*   Updated: 2024/10/14 19:11:39 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vec3_set_a(t_vec3 a, t_vec3 b)
{
	a[_X] = b[_X];
	a[_Y] = b[_Y];
	a[_Z] = b[_Z];
}

void	vec3_a_to_b(t_vec3 dir_out, t_vec3 point_a, t_vec3 point_b)
{
	dir_out[_X] = point_b[_X] - point_a[_X];
	dir_out[_Y] = point_b[_Y] - point_a[_Y];
	dir_out[_Z] = point_b[_Z] - point_a[_Z];
}

void	vec3_scale_add(t_vec3 dest, t_vec3 base, t_vec3 dir, float mag)
{
	t_vec3	scaled_direction;

	vec3_scaleize(scaled_direction, dir, mag);
	dest[_X] = base[_X] + scaled_direction[_X];
	dest[_Y] = base[_Y] + scaled_direction[_Y];
	dest[_Z] = base[_Z] + scaled_direction[_Z];
}
