/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:14:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 14:15:29 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	eq.a will always equal 1 in this equation so has been optimized out
int	intersect_light(t_light *light, t_ray *ray, float *t)
{
	float		temp_t;
	t_quadratic	eq;
	t_vec3		oc;

	vec3_a_to_b(oc, *ray->origin, light->point);
	eq.b = 2 * dot_product(oc, ray->udir);
	eq.c = dot_product(oc, oc) - (LIGHT_RAD * light->lum / 2);
	eq.discriminant = eq.b * eq.b - 4 * eq.c;
	if (eq.discriminant < 0)
		return (-1);
	temp_t = (eq.b - sqrt(eq.discriminant)) / 2;
	if (temp_t > EPSILON && temp_t < *t)
	{
		*t = temp_t;
		return (light->hue);
	}
	return (-1);
}

//	currently this function is redundant since we only have one light source
//	but it will be useful when there are multiple
void	intersect_lights(t_scene *scene, t_ray *ray, float *t, int *col)
{
	int		temp_color;
	float	temp_t;

	temp_color = -1;
	temp_t = *t;
	temp_color = intersect_light(&scene->light, ray, &temp_t);
	if ((temp_color >= 0) && temp_t < *t)
	{
		if (ray->origin == &scene->cam.point)
		{
			scene->screen_object[ray->y][ray->x] = &scene->light;
			scene->select_type[ray->y][ray->x] = SEL_LIGHT;
			ray->obj_type = SEL_LIGHT;
		}
		*col = temp_color;
		*t = temp_t;
	}
}
