/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:32:54 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:24:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_scene(t_scene *scene)
{
	free (scene->fname);
	free (scene->img);
	free (scene->cyls);
	free (scene->plns);
	free (scene->sphs);
	free (scene);
}

void	dealloc_shapes(t_scene **scenes, int i)
{
	while (i >= 0)
	{
		if (!scenes || !scenes[i])
			exit_error(NULL, "Error: failed deallocate shapes\n", ERR_NULLPTR);
		if (scenes[i]->sphs)
			free (scenes[i]->sphs);
		if (scenes[i]->plns)
			free (scenes[i]->plns);
		if (scenes[i]->cyls)
			free (scenes[i]->cyls);
	}
}
