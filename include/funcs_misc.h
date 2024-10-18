/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_misc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:48:44 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_MISC_H
# define FUNCS_MISC_H

//	check_format.c
int		check_format(int argc, char **argv);

void	display_hud(t_mlx *mlx, t_scene *scene);

//	utils_mlx.c
int		set_mlx(t_mlx *mlx, t_rt *rt);
void	cleanup_mlx(t_mlx *mlx);

#endif
