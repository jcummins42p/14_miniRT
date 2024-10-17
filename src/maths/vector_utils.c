/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:12:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:12:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

