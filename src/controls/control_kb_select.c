/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kb_select.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:29:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 17:29:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	k_deselect_object(t_mlx *mlx)
{
	mlx->rt->scenes[mlx->rt->curr_scene]->selected = NULL;
	mlx->rt->scenes[mlx->rt->curr_scene]->sel_type = SEL_CAM;
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

void	k_select_light(int keysym, t_mlx *mlx)
{
	t_scene	*scene;

	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	mlx->rt->scenes[mlx->rt->curr_scene]->selected = &scene->light;
	if (keysym == XK_p)
		mlx->rt->scenes[mlx->rt->curr_scene]->sel_type = SEL_LIGHT;
	else
		mlx->rt->scenes[mlx->rt->curr_scene]->sel_type = SEL_LIGHT_VALS;
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

void	k_select_ambient(t_mlx *mlx)
{
	t_scene	*scene;

	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	mlx->rt->scenes[mlx->rt->curr_scene]->selected = &scene->amb;
	mlx->rt->scenes[mlx->rt->curr_scene]->sel_type = SEL_AMBIENT;
}
