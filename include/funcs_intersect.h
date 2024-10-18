/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_intersect.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:48:53 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_INTERSECT_H
# define FUNCS_INTERSECT_H

// intersect_cylinder.c
void	intersect_cylinders(t_scene *scene, t_ray *ray, float *t, int *col);

// intersect_cylinder_caps.c
int		intersect_cyl_caps(t_cylinder *cylinder, t_ray *ray, float *t);

//	intersect_light.c
void	intersect_lights(t_scene *scene, t_ray *ray, float *t, int *col);

//	intersect_planes.c
void	intersect_planes(t_scene *scene, t_ray *ray, float *t, int *col);

//	intersect_spheres.c
void	intersect_spheres(t_scene *scene, t_ray *ray, float *t, int *col);

#endif
