/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:45:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_UTILS_H
# define FUNCS_UTILS_H

//	check_format.c
int		check_format(int argc, char **argv);

//	utils_mlx.c
int		set_mlx(t_mlx *mlx, t_rt *rt);
void	cleanup_mlx(t_mlx *mlx);

//	utils_rt.c
int		set_rt(int argc, char **argv, t_rt *rt);
void	cleanup_rt(t_rt *rt);

//	init.c
void	init_object_selection(t_scene *scene);
int		init_scene(t_scene *scene, char *filename, int id);
int		init_scenes(t_rt *rt, char **argv);
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
