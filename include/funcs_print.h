/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:35:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_PRINT_H
# define FUNCS_PRINT_H

//	print_uniqs.c
void	print_ambient(t_ambient *ambient);
void	print_camera(t_camera *camera);
void	print_light(t_light *light);
void	print_uniqs(t_scene *scene);

//	print_shapes.c
void	print_sphere(t_sphere sphere);
void	print_plane(t_plane plane);
void	print_cylinder(t_cylinder cylinder);
void	print_shapes(t_scene *scene);

//	print_scene.c
void	print_meta(t_scene *scene);
void	print_scene(t_scene *scene);
void	print_scenes(t_rt *rt);

//	print_utils.c
void	print_color(char *pre, char *mid, char *post, int color);
void	print_vec3(char *message, t_vec3 vec);

#endif
