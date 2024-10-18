/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:49:37 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 13:37:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	open_scenes(t_rt *rt, char **argv)
{
	int	i;

	i = -1;
	while (++i < rt->n_scenes)
	{
		rt->fd[i] = open(argv[i + 1], O_RDONLY);
		if (rt->fd[i] < 0)
			return (1);
	}
	return (0);
}

int	init_rt(t_rt *rt, int argc)
{
	rt->errcode = 0;
	rt->curr_scene = 0;
	rt->n_scenes = argc - 1;
	rt->fd = malloc(sizeof(int) * rt->n_scenes);
	if (!rt->fd)
		return (1);
	rt->scenes = alloc_scenes(rt->n_scenes);
	if (!rt->scenes)
		return (1);
	return (0);
}

int	set_rt(int argc, char **argv, t_rt *rt)
{
	if (init_rt(rt, argc))
		return (1);
	init_scenes(rt, argv);
	if (!rt->scenes)
		return (1);
	if (open_scenes(rt, argv))
		return (1);
	preparse(rt);
	if (alloc_shapes(rt))
		return (1);
	if (open_scenes(rt, argv))
		return (1);
	parse(rt);
	return (0);
}

void	cleanup_rt(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->n_scenes)
		free_scene(rt->scenes[i++]);
	free (rt->scenes);
	i = 0;
	while (i < rt->n_scenes)
	{
		if (rt->fd[i] < 0)
			break ;
		close (rt->fd[i++]);
	}
	free (rt->fd);
}
