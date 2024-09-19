/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 11:49:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_scenes(t_scene **scenes, int argc)
{
	int	n_scenes;
	int	i;

	n_scenes = argc - 1;
	i = 0;
	scenes = malloc(sizeof(t_scene *) * n_scenes);
	if (!scenes)
		exit_error("Malloc error", ERR_MALLOC);
	while (i < n_scenes)
		scenes[i++] = NULL;
	return (0);
}

int	open_scenes(int fd[], int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < (argc - 1))
	{
		fd[i] = open(argv[i + 1], O_RDONLY);
		if (fd[i] < 0)
			return (i);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene		**scenes;
	int			fd[argc - 1];
	int			errcode;

	scenes = NULL;
	errcode = 0;
	if (argc < 2)
		exit_error("Wrong number of arguments", 1);
	errcode = init_scenes(scenes, argc);
	errcode = open_scenes(fd, argc, argv);
	parse(fd, argc, scenes);
	return (0);
}
