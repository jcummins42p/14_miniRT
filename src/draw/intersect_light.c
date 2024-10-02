/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:14:47 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/02 18:29:47 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	eq.a will always equal 1 in this equation so has been optimized out
t_color	intersect_light(t_light *light, t_ray *ray, float *t)
{
	float		temp_t;
	t_quadratic	eq;
	t_vec3		oc;	//	points from cam origin to the sphere center

	vec3_a_to_b(oc, *ray->origin, light->point);
	eq.b = 2 * dot_product(oc, ray->udir);
	eq.c = dot_product(oc, oc) - (LIGHT_RAD * light->lum);
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
		if (ray->origin == &scene->cam.point)
		{
			pthread_mutex_lock(&scene->mutex);
			scene->screen_object[ray->y][ray->x] = &scene->light;
			scene->select_type[ray->y][ray->x] = SEL_LIGHT;
			pthread_mutex_unlock(&scene->mutex);
		}
		*t = temp_t;
	}
	return (pixel_color);
}

//	allocates value magnitude t to float pointer if direction vector is aligned
//	with unit vector, and returns 0 if t is a valid solution.
/*int	get_t(t_vec3 dir_vec, t_vec3 unit_vec, float *t)*/
/*{*/
	/*t_vec3	t;*/
	/*int		dimension;*/

	/*dimension = -1;*/
	/*zero_vector(t);*/
	/*while (++dimension < 3)*/
	/*{*/
		/*if (dir_vec[dimension] > EPSILON && unit_vec[dimension] > EPSILON)*/
			/*t[dimension] = (dir_vec[dimension] / unit_vec[dimension]);*/
	/*}*/
	/*dimension = -1;*/
	/*while (++dimension < 3)*/

/*}*/

//	the dot (or scalar) product of two parallel vectors equals the product of
//	their magnitudes.
//	We know the unit vector of the camera ray and full euclidean from camera
//	to light.
//	C (camera position) - position vector
//	R (ray direction) - unit vector
//	L (light position) - position vector
//	t = time
//	t = (L - C) / R
//	for point L to lie on ray R, t must be positive (in front of the camera)
//	A single solution t must exist for all components of the direction vector
//	L - C = cam_to_light direction vector
//	so t = cam_to_light direction vector / ray unit vector
/*t_color	intersect_light(t_light *light, t_ray *ray, float *t)*/
/*{*/
	/*float		temp_t;*/
	/*t_vec3		cam_to_light;*/
	/*float		denominator;*/

	/*denominator = dot_product(ray->udir, plane->norm);*/
	/*if (fl_abs(denominator) > EPSILON)*/
	/*{*/
		/*vec3_a_to_b(cam_to_anch, *ray->origin, plane->anch);*/
		/*temp_t = dot_product(cam_to_anch, plane->norm) / (denominator);*/
		/*if (temp_t > 0.001 && temp_t < *t)*/
		/*{*/
			/**t = temp_t;*/
			/*return (plane->color);*/
		/*}*/
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

