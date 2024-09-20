/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 18:21:58 by jcummins         ###   ########.fr       */
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
	ft_printf("Mouserelease: %d\n", button);
	(void) vars;
	return (0);
}

int	b_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	ft_printf("Keypress: %d\n", button);
	if (button == ON_DESTROY)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}
