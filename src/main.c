/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 14:53:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene **alloc_scenes(int n_scenes)
{
	int	i;
	t_scene	**scenes;

	i = 0;
	scenes = malloc(n_scenes * sizeof(t_scene *));
	if (!scenes)
		return (NULL);
	while (i < n_scenes)
	{
		scenes[i] = malloc(sizeof(t_scene));
		if (!scenes[i])
		{
			while (i-- > 0)
				free(scenes[i]);
			free(scenes);
			return (NULL);
		}
		i++;
	}
	return (scenes);
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

	errcode = 0;
	if (argc < 2)
		exit_error("Wrong number of arguments", 1);
	scenes = alloc_scenes(argc - 1);
	errcode = open_scenes(fd, argc, argv);
	parse(fd, argc, scenes);
	return (0);
}
