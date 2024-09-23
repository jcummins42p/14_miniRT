/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:45:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 14:54:51 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_listcount(char **list)
{
	int count;

	count = 0;
	if (!list)
		return (count);
	while (list[count])
		count++;
	return (count);
}

void	parse_sphere(char *input, t_scene *scene)
{
	char	**items;
	int		i;

	i = 0;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_plane, init to default\n");
	else
	{
		while (scene->sphs[i].id >= 0)
			i++;
		items = ft_split(input, ' ');
		if (!items || ft_listcount(items) != 4)
		{
			scene->valid = false;
			ft_free_string_list(items);
			return ;
		}
		scene->sphs[i].id = i;
		set_vector(scene->sphs[i].center, items[1]);
		scene->sphs[i].diamtr = ft_atof(items[2]);
		scene->sphs[i].color = set_color(items[3]);
		aa_bound_sphere(&scene->sphs[i]);
		ft_free_string_list(items);
	}
}

void	parse_plane(char *input, t_scene *scene)
{
	char	**items;
	int		i;

	i = 0;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_plane, init to default\n");
	else
	{
		while (scene->plns[i].id >= 0)
			i++;
		items = ft_split(input, ' ');
		if (!items || ft_listcount(items) != 4)
		{
			scene->valid = false;
			ft_free_string_list(items);
			return ;
		}
		scene->plns[i].id = i;
		set_vector(scene->plns[i].anch, items[1]);
		if (set_unit_vector(scene->plns[i].norm, items[2]))
			scene->valid = false;
		scene->plns[i].color = set_color(items[3]);
		ft_free_string_list(items);
	}
}

void	parse_cylinder(char *input, t_scene *scene)
{
	char	**items;
	int		i;

	i = 0;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_plane, init to default\n");
	else
	{
		while (scene->cyls[i].id >= 0)
			i++;
		items = ft_split(input, ' ');
		if (!items || ft_listcount(items) != 6)
		{
			scene->valid = false;
			return ;
		}
		scene->cyls[i].id = i;
		set_vector(scene->cyls[i].center, items[1]);
		if (set_unit_vector(scene->cyls[i].axis, items[2]))
			scene->valid = false;
		scene->cyls[i].diamtr = ft_atof(items[3]);
		scene->cyls[i].height = ft_atof(items[4]);
		scene->cyls[i].color = set_color(items[5]);
		aa_bound_capsule(&scene->cyls[i]);
		ft_free_string_list(items);
	}
}
