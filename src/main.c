/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/04 17:05:53 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_rt	rt;

	if (argc < 2)
		exit_error(NULL, "Error: Wrong number of arguments\n", ERR_ARGC);
	if (check_format(argc, argv))
		exit_error(NULL, "", ERR_ARGC);
	if (set_mlx(&mlx, &rt))
		exit_error(&mlx, "Error: Failure to initialize mlx\n", ERR_ARGC);
	if (set_rt(argc, argv, &rt))
		exit_error(&mlx, "Error: Failure to parse input files\n", ERR_ARGC);
	print_scenes(&rt);
	render_scene(&mlx, rt.scenes[0]);
	mlx_loop(mlx.mlx);
	cleanup_mlx(&mlx);
	return (rt.errcode);
}
