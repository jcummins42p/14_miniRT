/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/26 15:41:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	b_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	b_release(int button, void *vars)
{
	(void)button;
	/*ft_printf("Mouserelease: %d\n", button);*/
	(void) vars;
	return (0);
}

void	m_zoom(t_mlx *mlx, int button)
{
	if (button == ON_MOUSEDOWN)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_Z]
			+= 1 * mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z];
	else if (button == ON_MOUSEUP)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_Z]
			-= 1 * mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z];
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

int	b_press(int button, int x, int y, t_mlx *mlx)
{
	if (button == ON_MOUSEDOWN || button == ON_MOUSEUP)
		m_zoom(mlx, button);
	printf("Mousepress: x:%-4d y:%-4d\n", x, y);
	if (button == ON_DESTROY)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}
