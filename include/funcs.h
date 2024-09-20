/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 15:52:29 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

//	parse_attributes.c
int		set_colors(char *input);
void	zero_vector(t_vector vec);
void	print_color(char *pre, char *mid, char *post, int color);
void	set_vector(t_vector vec, char *input);
void	print_vector(char *message, t_vector vec);

//	parse_uniqs.c
void	parse_ambient(char *input, t_scene *scene);
void	parse_camera(char *input, t_scene *scene);
void	parse_light(char *input, t_scene *scene);

//	print_uniqs.c
void	print_ambient(t_ambient ambient);
void	print_camera(t_camera camera);
void	print_light(t_light light);
void	print_uniqs(t_scene *scene);

//	print_shapes.c
void	print_sphere(t_sphere sphere);
void	print_plane(t_plane plane);
void	print_cylinder(t_cylinder cylinder);
void	print_shapes(t_scene *scene);

//	print_scene.c
void	print_meta(t_scene *scene);
void	print_scene(t_scene *scene);
void	print_scenes(t_scene **scene, int n_scenes);

//	parse_shapes.c
void	parse_sphere(char *input, t_scene *scene);
void	parse_plane(char *input, t_scene *scene);
void	parse_cylinder(char *input, t_scene *scene);

//	preparse.c
void	preparse(int fd[], t_scene **scenes, int n_scenes);

//	parse.c
void	parse(int *fd, int argc, t_scene **scenes);

//	init.c
void	init_scene(t_scene *scene, char *filename, int id);
void	init_scenes(t_scene **scenes, char **argv, int n_scenes);
void	init_spheres(t_scene *scene);
void	init_planes(t_scene *scene);
void	init_cylinders(t_scene *scene);

//	error.c
void	exit_error(char *message, int errcode);

//	utils_alloc.c
int		alloc_shapes(t_scene **scenes, int n_scenes);
t_scene	**alloc_scenes(int n_scenes);

//	utils_free.c
void	free_scene(t_scene *scene);
void	free_scenes(t_scene **scenes, int n_scenes);
void	dealloc_shapes(t_scene **scenes, int i);

#endif
