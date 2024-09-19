/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:32:54 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 20:37:07 by jcummins         ###   ########.fr       */
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
	free (scenes);
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
