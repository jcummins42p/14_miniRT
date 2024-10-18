/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_draw.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:08:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_DRAW_H
# define FUNCS_DRAW_H

//	cast_cam_ray.c
void	prep_cam_ray(t_mlx *mlx, t_scene *scene, int x, int y);

//	cast_light_ray.c
int		prep_light_ray(t_scene *scene, t_vec3 bounce_point);

//	draw_color.c
int		color_invert(int original);
int		color_illuminate(int original, int target, float ratio);
int		color_subtract(int original, int target, float ratio);
int		color_addition(int original, int target);
int		color_shift(int original, int target, float ratio);

//	draw_utils.c
int		img_init(t_mlx *mlx, t_img *img);
void	pixel_put_img(t_img *img, int x, int y, int color);
void	color_int_to_vector(t_rgb rgb, int color);
int		color_vector_to_int(t_rgb rgb);

//	light_angle.c
int 	light_angle(t_scene *scene, t_ray *ray, int lighint);

//	pixel_shaders.c
int		shade_pixel_distance(int pixel_color, float distance);
int		shade_light_distance(int pixel_color, float distance, float lum);
int		combine_lights(int light_color, t_ambient amb);
int		illuminate_pixel(int pixel_color, int lighint);

//	post_process.c
void	post_process(t_scene *scene);

//	ray_utils.c
void	norm_device_coords(t_vec2 ndc, int x, int y);
void	project_viewport(t_vec2 project, t_vec2 ndc, int fov, float aspect);
void	set_ray_direction(t_vec3 dir, t_vec2 plane, t_camera cam);

//	render_scene_mt.c
int		render_scene_mt(t_mlx *mlx, t_scene *scene);

//	render_scene_st.c
int		render_scene(t_mlx *mlx, t_scene *scene);

//	specular.c
void	specular_pass(t_scene *scene, t_ray *ray, int *pixel_color);

#endif
