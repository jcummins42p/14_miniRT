/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 14:45:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	fl_abs(float f)
{
	if (f < 0)
		f = -f;
	return (f);
}

float	vector_length(t_vector vec)
{
	return (sqrtf((vec[0] * vec[0])
			+ (vec[1] * vec[1])
			+ (vec[2] * vec[2])));
}

//	stores the unit vector of 'direction' in 'unit'
void	vector_normalize(t_vector unit, t_vector direction)
{
	float		v_len;

	v_len = vector_length(direction);
	if (v_len != 0)
	{
		unit[0] = direction[0] / v_len;
		unit[1] = direction[1] / v_len;
		unit[2] = direction[2] / v_len;
	}
}
