/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_control.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:37 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_CONTROL_H
# define FUNCS_CONTROL_H

//	control_shine.c
void	k_adjust_shine(int keysym, t_mlx *mlx);

//	control_scenes.c
int		k_select_scene(int keysym, t_mlx *mlx);

//	control_move_shapes.c
void	k_move_plane(int keysym, t_scene *scene);
void	k_move_sphere(int keysym, t_scene *scene);

// control_move_cylinder
void	k_move_cylinder(int keysym, t_scene *scene);

//	control_move.c
void	k_move_light(int keysym, t_scene *scene);
void	rotate_quaternion(t_scene *scene, int axis, float incr);
void	k_rotate(t_scene *scene, int keysym);
void	k_move_camera(int keysym, t_scene *scene);
void	k_directional_controls(int keysym, t_mlx *mlx);

//	control_kb_select.c
void	k_deselect_object(t_mlx *mlx);
void	k_select_light(int keysym, t_mlx *mlx);
void	k_select_ambient(t_mlx *mlx);

//	control_camera.c
void	reset_cam_default(t_mlx *mlx, t_camera *cam);
void	k_cam_pan(int keysym, t_camera *cam);

//	control_hue.c
void	k_control_ambient(int keysym, t_scene *scene);
void	k_control_light(int keysym, t_scene *scene);

//	hookhandle_kb.c
int		k_no_event(void *vars);
int		k_release(int keysym, void *vars);
void	k_fov_controls(t_mlx *mlx, int ksym);
int		k_press(int keysym, t_mlx *mlx);

//	hookhandle_mouse.c
int		b_no_event(void *vars);
int		b_press(int button, int x, int y, t_mlx *mlx);
int		b_release(int button, void *vars);

//	quaternion.c
t_quat	axis_angle_to_quaternion(t_vec3 axis, float angle);
t_quat	quaternion_multiply(t_quat q1, t_quat q2);
t_quat	quaternion_conjugate(t_quat q);
void	rotate_vector_by_quaternion(t_vec3 vector, t_quat q);

#endif
