/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/22 09:52:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

//	draw.c
void	render_scene(t_mlx *mlx, t_scene *scene);

//	hud.c
void	display_hud(t_mlx *mlx, t_scene *scene);

//	hookhandle_mouse.c
int		b_no_event(void *vars);
int		b_press(int button, int x, int y, t_mlx *mlx);
int		b_release(int button, void *vars);

//	hookhandle_kb.c
int		k_no_event(void *vars);
int		k_release(int keysym, void *vars);
int		k_press(int keysym, t_mlx *mlx);

//	parse_attributes.c
int		set_color(char *input);
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
void	print_scenes(t_rt *rt);

//	parse_shapes.c
void	parse_sphere(char *input, t_scene *scene);
void	parse_plane(char *input, t_scene *scene);
void	parse_cylinder(char *input, t_scene *scene);

//	preparse.c
void	preparse(t_rt *rt);

//	parse.c
void	parse(t_rt *rt);

//	init.c
void	init_scene(t_scene *scene, char *filename, int id);
void	init_scenes(t_rt *rt, char **argv);
void	init_spheres(t_scene *scene);
void	init_planes(t_scene *scene);
void	init_cylinders(t_scene *scene);

//	error.c
void	exit_error(char *message, int errcode);

//	utils_alloc.c
int		alloc_shapes(t_rt *rt);
t_scene	**alloc_scenes(int n_scenes);

//	utils_free.c
void	free_scene(t_scene *scene);
void	free_rt(t_rt *rt);
void	dealloc_shapes(t_scene **scenes, int i);

#endif
