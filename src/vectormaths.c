/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 13:56:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	fl_abs(float f)
{
	if (f < 0)
		f = -f;
	return (f);
}

void	cross_product(t_vector product, t_vector a, t_vector b)
{
	product[_X] = a[_Y] * b[_Z] - a[_Z] * b[_Y];
	product[_Y] = a[_Z] * b[_X] - a[_X] * b[_Z];
	product[_Z] = a[_X] * b[_Y] - a[_Y] * b[_X];
}

float	dot_product(t_vector a, t_vector b)
{
	return (a[_X] * b[_X] + a[_Y] * b[_Y] + a[_Z] * b[_Z]);
}

void	vector_scaleize(t_vector scalar, t_vector unit, float magnitude)
{
	scalar[_X] = unit[_X] * magnitude;
	scalar[_Y] = unit[_Y] * magnitude;
	scalar[_Z] = unit[_Z] * magnitude;
}

float	vector_length(t_vector vec)
{
	return (sqrtf((vec[_X] * vec[_X])
			+ (vec[_Y] * vec[_Y])
			+ (vec[_Z] * vec[_Z])));
}

//	stores the unit vector of 'direction' in 'unit'
void	vector_normalize(t_vector unit, t_vector direction)
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
