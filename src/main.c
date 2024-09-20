/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 14:04:00 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	open_scenes(int fd[], int n_scenes, char **argv)
{
	int	i;

	i = -1;
	while (++i < (n_scenes))
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
	int			*fd;
	int			errcode;

	errcode = 0;
	fd = malloc(sizeof(int) * argc - 1);
	if (argc < 2)
		exit_error("Error: Wrong number of arguments", ERR_ARGC);
	scenes = alloc_scenes(argc - 1);
	init_scenes(scenes, argv, argc - 1);
	if (!scenes)
		exit_error("Error: Failure to malloc scenes", ERR_MALLOC);
	if (open_scenes(fd, argc - 1, argv))
		exit_error("Error: Failure to open files", ERR_ARGV);
	preparse(fd, scenes, argc - 1);
	alloc_shapes(scenes, argc - 1);
	open_scenes(fd, argc - 1, argv);
	parse(fd, argc, scenes);
	print_scenes(scenes, argc - 1);
	free_scenes(scenes, argc - 1);
	free(fd);
	return (0);
}
