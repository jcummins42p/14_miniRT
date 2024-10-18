/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_maths.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:15:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_MATHS_H
# define FUNCS_MATHS_H

//	vectormaths.c
void	toggle_bool(bool *current);
float	fl_abs(float f);

// quadratic.c
int		calculate_quadratic(t_cylinder *cylinder, t_ray *ray,
			t_quadratic *eq);

//	vector_maths.c
void	vec3_scale_add(t_vec3 dest, t_vec3 base, t_vec3 direction, float magnitude);
void	vec3_position(t_vec3 dest, t_vec3 origin, t_vec3 unit, float magnitude);
void	vec3_a_to_b(t_vec3 dir_out, t_vec3 point_a, t_vec3 point_b);
void	vec3_scaleize(t_vec3 scalar, t_vec3 unit, float magnitude);
void	vec3_normalize(t_vec3 unit, t_vec3 direction);

//	vector_normals.c
void	vec3_surface_reflection(t_vec3 reflect, t_vec3 light, t_vec3 norm);
void 	get_cylinder_normal(t_vec3 normal, t_cylinder *cylinder, t_ray *ray);

//	vector_products.c
void	cross_product(t_vec3 product, t_vec3 a, t_vec3 b);
float	dot_product(t_vec3 a, t_vec3 b);

//	vector_utils.c
void	vec3_set_a(t_vec3 a, t_vec3 b);
void	vec3_invert(t_vec3 vec);
float	vec3_length(t_vec3 vec);

#endif
