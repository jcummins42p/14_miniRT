/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:20:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_PARSE_H
# define FUNCS_PARSE_H

//	parse.c
void	parse(t_rt *rt);

//	parse_attributes.c
int		set_color(char *input);
void	zero_vec3(t_vec3 vec);
int		set_vec3(t_vec3 vec, char *input);
int		set_unit_vec3(t_vec3 vec, char *input);

//	parse_shapes.c
void	parse_sphere(char *input, t_scene *scene);
void	parse_plane(char *input, t_scene *scene);
void	parse_cylinder(char *input, t_scene *scene);

//	parse_uniqs.c
void	orient_camera(t_camera *camera);
void	parse_ambient(char *input, t_scene *scene);
void	parse_camera(char *input, t_scene *scene);
void	parse_light(char *input, t_scene *scene);

//	preparse.c
void	preparse(t_rt *rt);

#endif
