/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_products.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 21:03:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
