/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:22:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vec3_set_a(t_vec3 a, t_vec3 b)
{
	a[_X] = b[_X];
	a[_Y] = b[_Y];
	a[_Z] = b[_Z];
}

float	vec3_length(t_vec3 vec)
{
	return (sqrtf((vec[_X] * vec[_X])
			+ (vec[_Y] * vec[_Y])
			+ (vec[_Z] * vec[_Z])));
}

void	vec3_invert(t_vec3 vec)
{
	vec[_X] = 0 - vec[_X];
	vec[_Y] = 0 - vec[_Y];
	vec[_Z] = 0 - vec[_Z];
}
