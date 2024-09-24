/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 20:31:53 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	fl_abs(float f)
{
	if (f < 0)
		f = -f;
	return (f);
}

void	cross_product(t_vec3 product, t_vec3 a, t_vec3 b)
{
	product[_X] = a[_Y] * b[_Z] - a[_Z] * b[_Y];
	product[_Y] = a[_Z] * b[_X] - a[_X] * b[_Z];
	product[_Z] = a[_X] * b[_Y] - a[_Y] * b[_X];
}

float	dot_product(t_vec3 a, t_vec3 b)
{
	return (a[_X] * b[_X] + a[_Y] * b[_Y] + a[_Z] * b[_Z]);
}

void	vector_scaleize(t_vec3 scalar, t_vec3 unit, float magnitude)
{
	scalar[_X] = unit[_X] * magnitude;
	scalar[_Y] = unit[_Y] * magnitude;
	scalar[_Z] = unit[_Z] * magnitude;
}

float	vector_length(t_vec3 vec)
{
	return (sqrtf((vec[_X] * vec[_X])
			+ (vec[_Y] * vec[_Y])
			+ (vec[_Z] * vec[_Z])));
}

//	stores the unit vector of 'direction' in 'unit'
void	vector_normalize(t_vec3 unit, t_vec3 direction)
{
	float		v_len;

	v_len = vector_length(direction);
	if (v_len != 0)
	{
		unit[_X] = direction[_X] / v_len;
		unit[_Y] = direction[_Y] / v_len;
		unit[_Z] = direction[_Z] / v_len;
	}
}
