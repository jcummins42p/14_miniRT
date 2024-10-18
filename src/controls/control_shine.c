/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_shine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:15:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 15:47:03 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	k_adjust_shine_cylinder(int keysym, t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	if (keysym == XK_COMMA)
		cylinder->shine -= 8;
	else if (keysym == XK_PERIOD)
		cylinder->shine += 8;
	if (cylinder->shine < 2)
		cylinder->shine = 2;
	else if (cylinder->shine > 256)
		cylinder->shine = 256;
}

static void	k_adjust_shine_plane(int keysym, t_plane *plane)
{
	if (!plane)
		return ;
	if (keysym == XK_COMMA)
		plane->shine -= 8;
	else if (keysym == XK_PERIOD)
		plane->shine += 8;
	if (plane->shine < 2)
		plane->shine = 2;
	else if (plane->shine > 256)
		plane->shine = 256;
}

static void	k_adjust_shine_sphere(int keysym, t_sphere *sphere)
{
	if (!sphere)
		return ;
	if (keysym == XK_COMMA)
		sphere->shine -= 8;
	else if (keysym == XK_PERIOD)
		sphere->shine += 8;
	if (sphere->shine < 2)
		sphere->shine = 2;
	else if (sphere->shine > 256)
		sphere->shine = 256;
}

void	k_adjust_shine(int keysym, t_mlx *mlx)
{
	void	*sel_obj;
	int		sel_type;

	sel_type = mlx->rt->scenes[mlx->rt->curr_scene]->sel_type;
	sel_obj = mlx->rt->scenes[mlx->rt->curr_scene]->selected;
	if (keysym == XK_BACKSLASH)
		toggle_bool(&mlx->rt->scenes[mlx->rt->curr_scene]->specular);
	else if (sel_type < SEL_SPHERE || sel_type > SEL_CYLINDER_SIDE)
		return ;
	else if (sel_type == SEL_SPHERE)
		k_adjust_shine_sphere(keysym, sel_obj);
	else if (sel_type == SEL_PLANE)
		k_adjust_shine_plane(keysym, sel_obj);
	else if (sel_type == SEL_CYLINDER_SIDE || sel_type == SEL_CYLINDER_CAP)
		k_adjust_shine_cylinder(keysym, sel_obj);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}
