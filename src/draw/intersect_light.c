/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:14:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/30 13:20:48 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	returns t magnitude of euclid_vec given a unit vector, stores it in t
//	returns 0 if sucessful, 1 if there is not a solution
/*int	find_magnitude(t_vec3 euclidian, t_vec3 unit, float *t)*/
/*{*/
	/*vec3	temp_t;*/
	/*float	output;*/
	/*int		valid[3];*/
	/*int		i;*/

	/*i = 0;*/
	/*zero_vector(temp_t);*/
	/*while (i < 3)*/
	/*{*/
		/*valid[i] = 0;*/
		/*if (euclidian[i] > EPSILON)*/
		/*{*/
			/*if (unit[i] < EPSILON)*/
				/*return (1);*/
			/*temp_t[i] = euclidian[i] / unit[i];*/
			/*output = temp_t[i];*/
			/*valid[i] = 1;*/
		/*}*/
		/*i++;*/
	/*}*/
	/*i = 0;*/
	/*while (i < 3)*/
	/*{*/
		/*if (valid[i] && temp_t[i])*/

	/*}*/
	/*return (0);*/
/*}*/

t_color	intersect_light(t_light *light, t_ray *ray, float *t)
{
	float		temp_t;
	t_quadratic	eq;
	t_vec3		oc;	//	points from cam origin to the sphere center

	vec3_a_to_b(oc, *ray->origin, light->point);
	eq.a = dot_product(ray->udir, ray->udir);
	eq.b = 2 * dot_product(oc, ray->udir);
	eq.c = dot_product(oc, oc) - (LIGHT_RAD * LIGHT_RAD * light->lum);
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (-1);
	temp_t = (eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	if (temp_t > 0.001 && temp_t < *t)
	{
		*t = temp_t;
		return (light->hue);
	}
	return (-1);
}

t_color	intersect_lights(t_scene *scene, t_ray *ray, float *t)
{
	t_color	temp_color;
	t_color	pixel_color;
	float	temp_t;
	int		i;

	i = 0;
	temp_color = -1;
	pixel_color = -1;
	temp_t = *t;
	temp_color = intersect_light(&scene->light, ray, &temp_t);
	if ((temp_color >= 0) && temp_t < *t)
	{
		pixel_color = temp_color;
		*t = temp_t;
	}
	return (pixel_color);
}
