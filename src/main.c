/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 18:31:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_scene(t_scene *scene)
{
	free (scene->fname);
	free (scene->cyls);
	free (scene->plns);
	free (scene->sphs);
	free (scene);
}

void	free_scenes(t_scene **scenes, int n_scenes)
{
	int	i;

	i = 0;
	while (i < n_scenes)
		free_scene(scenes[i++]);
}

void	init_scene(t_scene *scene, char *filename, int id)
{
	scene->fname = ft_strdup(filename);
	scene->id = id;
	scene->n_cylinders = 0;
	scene->n_planes = 0;
	scene->n_spheres = 0;
	scene->sky = 0x420000;
	scene->amb.lock = false;
	scene->amb.lum = 0.2;
	scene->amb.hue = 0xFFFFFF;
	scene->cam.lock = false;
	set_vector(scene->cam.point, "-50,0,20");
	set_vector(scene->cam.dir, "-50,0,20");
	scene->cam.fov = 70;
	scene->light.lock = false;
	set_vector(scene->light.point, "-40,50,0");
	scene->light.lum = 0.6;
	scene->light.hue = 0x0A00FF;
	scene->cyls = NULL;
	scene->plns = NULL;
	scene->sphs = NULL;
}

void	init_scenes(t_scene **scenes, char **argv, int n_scenes)
{
	int	i;

	i = -1;
	while (++i < n_scenes)
		init_scene(scenes[i], argv[i + 1], i);
}

t_scene	**alloc_scenes(int n_scenes)
{
	t_scene	**scenes;
	int		i;

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

void	preparse_select(char *line, t_scene *scene)
{
	if (!ft_strncmp(line, "sp", 2))
		scene->n_spheres++;
	else if (!ft_strncmp(line, "pl", 2))
		scene->n_planes++;
	else if (!ft_strncmp(line, "cy", 2))
		scene->n_cylinders++;
}

void	dealloc_shapes(t_scene **scenes, int i)
{
	printf("Deallocating shapes from memory due to error\n");
	while (i >= 0)
	{
		if (!scenes || !scenes[i])
			exit_error("Error: failure to deallocate shapes\n", ERR_NULLPTR);
		if (scenes[i]->sphs)
			free (scenes[i]->sphs);
		if (scenes[i]->plns)
			free (scenes[i]->plns);
		if (scenes[i]->cyls)
			free (scenes[i]->cyls);
	}
}

int	alloc_shapes(t_scene **scenes, int n_scenes)
{
	int	i;

	i = -1;
	while (++i < n_scenes)
	{
		scenes[i]->cyls = malloc(sizeof(t_cylinder) * scenes[i]->n_cylinders);
		scenes[i]->plns = malloc(sizeof(t_plane) * scenes[i]->n_planes);
		scenes[i]->sphs = malloc(sizeof(t_sphere) * scenes[i]->n_spheres);
		if (scenes[i]->cyls == NULL
			|| scenes[i]->plns == NULL
			|| scenes[i]->sphs == NULL)
		{
			printf("Error: failure to malloc shapes");
			dealloc_shapes(scenes, i);
			return (1);
		}
	}
	return (0);
}

void	preparse(int fd[], t_scene **scenes, int n_scenes)
{
	char	*line;
	int		i;

	i = -1;
	printf("Pre-parsing input to set number of shapes\n");
	while (++i < n_scenes)
	{
		line = NULL;
		line = get_next_line(fd[i]);
		while (line)
		{
			preparse_select(line, scenes[i]);
			free (line);
			line = get_next_line(fd[i]);
		}
	}
	i = 0;
	while (i < n_scenes)
	{
		printf("Scene %d: spheres: %d, planes: %d, cylinders: %d\n", scenes[i]->id, scenes[i]->n_spheres, scenes[i]->n_planes, scenes[i]->n_cylinders);
		close (fd[i++]);
	}
}

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
	free_scenes(scenes, argc - 1);
	return (0);
}
