/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/21 17:33:10 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	k_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	k_release(int keysym, void *vars)
{
	ft_printf("Keyrelease: %d\n", keysym);
	(void) vars;
	return (0);
}

int	keysym_translate(int keysym)
{
	int	output;

	output = -1;
	if (keysym == XK_0)
		output = 0;
	else if (keysym == XK_1)
		output = 1;
	else if (keysym == XK_2)
		output = 2;
	else if (keysym == XK_3)
		output = 3;
	else if (keysym == XK_4)
		output = 4;
	else if (keysym == XK_5)
		output = 5;
	else if (keysym == XK_6)
		output = 6;
	else if (keysym == XK_7)
		output = 7;
	else if (keysym == XK_8)
		output = 8;
	else if (keysym == XK_9)
		output = 9;
	printf("Pressed numkey %d\n", output);
	return (output);
}

int	k_select(int keysym, t_mlx *mlx)
{
	int newscene;

	newscene = -1;
	newscene = keysym_translate(keysym);
	if (newscene >= 0 && newscene < mlx->rt->n_scenes)
	{
		printf("Acessing scene %d\n", newscene);
		mlx->rt->curr_scene = newscene;
		print_scene(mlx->rt->scenes[newscene]);
		render_scene(mlx, mlx->rt->scenes[newscene]);
		display_hud(mlx, mlx->rt->scenes[newscene]);
	}
	else
		printf("Invalid scene selected\n");
	return 0;
}

void	toggle_scan(t_mlx *mlx)
{
	int i;

	i = mlx->rt->curr_scene;
	if (mlx->rt->scenes[i]->rend.scan)
		mlx->rt->scenes[i]->rend.scan = false;
	else
		mlx->rt->scenes[i]->rend.scan = true;
}

int	k_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		ft_printf("escape pressed\n");
		mlx_loop_end(mlx->mlx);
	}
	/*if (keysym == 115)*/
		/*toggle_scan(mlx);*/
	else
		k_select(keysym, mlx);
	ft_printf("Keypress: %d\n", keysym);
	return (0);
}
