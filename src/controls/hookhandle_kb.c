/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 18:05:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	k_no_event(void *vars)
{
	(void) vars;
	return (0);
}

	/*ft_printf("Keyrelease: %d\n", keysym);*/
int	k_release(int keysym, void *vars)
{
	(void) vars;
	(void) keysym;
	return (0);
}

void	toggle_bool(bool *current)
{
	if (*current)
		*current = false;
	else
		*current = true;
}

void	k_redraw(t_mlx *mlx, int redraw)
{
	if (redraw == 2)
		print_scene(mlx->rt->scenes[mlx->rt->curr_scene]);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
	if (redraw == 2)
		display_hud(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

int	k_press(int keysym, t_mlx *mlx)
{
	printf("k_press %d\n", keysym);
	if (keysym == XK_Escape)
		mlx_loop_end(mlx->mlx);
	else if (keysym == XK_KP_5)
		reset_cam_default(mlx, &mlx->rt->scenes[mlx->rt->curr_scene]->cam);
	else if (keysym == XK_KP_Delete)
		k_deselect_object(mlx);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract
		|| keysym == XK_KP_Enter)
		k_select_scene(keysym, mlx);
	else if (keysym == XK_m)
		toggle_bool(&mlx->multithread);
	else if (keysym == XK_a)
		k_select_ambient(mlx);
	else if (keysym == XK_p || keysym == XK_l)
		k_select_light(keysym, mlx);
	else if (keysym == XK_period || keysym == XK_comma)
		k_adjust_shine(keysym, mlx);
	else if ((keysym >= XK_KP_7 && keysym <= XK_KP_0)
		|| keysym >= 100 || keysym <= 119)
		k_directional_controls(keysym, mlx);
	return (0);
}
