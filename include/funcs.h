/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/25 14:29:07 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

//	draw_color.c
void	color_int_to_vector(t_rgb rgb, t_color color);
int		color_vector_to_int(t_rgb rgb);
t_color	color_gradient(t_color original, t_color target, float ratio);

//	intersections_planes.c
int		intersect_planes(t_scene *scene, t_ray *ray, float *t);
int		intersect_spheres(t_scene *scene, t_ray *ray, float *t);

//	intersections_spheres.c

//	utils_mlx.c
int		set_mlx(t_mlx *mlx, t_rt *rt);
void	cleanup_mlx(t_mlx *mlx);

//	utils_rt.c
int		set_rt(int argc, char **argv, t_rt *rt);
void	cleanup_rt(t_rt *rt);

//	vectormaths.c
float	fl_abs(float f);

//	vector_products.c
void	cross_product(t_vec3 product, t_vec3 a, t_vec3 b);
float	dot_product(t_vec3 a, t_vec3 b);

//
void	vec3_a_to_b(t_vec3 dir_out, t_vec3 point_a, t_vec3 point_b);
float	vec3_length(t_vec3 vec);
void	vec3_normalize(t_vec3 unit, t_vec3 direction);
void	vec3_scaleize(t_vec3 scalar, t_vec3 unit, float magnitude);

//	bounding_aa.c
void	aa_bound_sphere(t_sphere *sphere);
void	aa_bound_capsule(t_cylinder *cylinder);

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
void	zero_vector(t_vec3 vec);
void	print_color(char *pre, char *mid, char *post, int color);
void	set_vec3(t_vec3 vec, char *input);
int		set_unit_vec3(t_vec3 vec, char *input);
void	print_vec3(char *message, t_vec3 vec);

//	parse_uniqs.c
void	parse_ambient(char *input, t_scene *scene);
void	parse_camera(char *input, t_scene *scene);
void	parse_light(char *input, t_scene *scene);

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
void	exit_error(t_mlx *mlx, char *message, int errcode);

//	utils_alloc.c
int		alloc_shapes(t_rt *rt);
t_scene	**alloc_scenes(int n_scenes);

//	utils_free.c
void	free_scene(t_scene *scene);
void	free_rt(t_rt *rt);
void	dealloc_shapes(t_scene **scenes, int i);

#endif
