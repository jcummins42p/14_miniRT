/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:45:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/15 17:39:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_listcount(char **list)
{
	int	count;

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
		printf("Error: NULL string passed to parse_sphere, init to default\n");
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
		set_vec3(scene->sphs[i].center, items[1]);
		scene->sphs[i].diamtr = ft_atof(items[2]);
		scene->sphs[i].shine = 32;
		scene->sphs[i].radius = scene->sphs[i].diamtr / 2;
		scene->sphs[i].color = set_color(items[3]);
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
		set_vec3(scene->plns[i].anch, items[1]);
		if (set_unit_vec3(scene->plns[i].norm, items[2]))
			scene->valid = false;
		scene->plns[i].color = set_color(items[3]);
		scene->plns[i].shine = 32;
		ft_free_string_list(items);
	}
}

int	set_cylinder_info(char **items, t_cylinder *cylinder)
{
	set_vec3(cylinder->center, items[1]);
	if (set_unit_vec3(cylinder->axis, items[2]))
		return (1);
	cylinder->diamtr = ft_atof(items[3]);
	cylinder->radius = cylinder->diamtr / 2;
	cylinder->height = ft_atof(items[4]);
	cylinder->color = set_color(items[5]);
	cylinder->shine = 32;
	aa_bound_capsule(cylinder);
	return (0);
}

void	parse_cylinder(char *input, t_scene *scene)
{
	char	**items;
	int		i;

	i = 0;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_cylinder, init to default\n");
	else
	{
		while (scene->cyls[i].id >= 0)
			i++;
		items = ft_split(input, ' ');
		scene->cyls[i].id = i;
		if (!items || ft_listcount(items) != 6)
			scene->valid = false;
		else if (set_cylinder_info(items, &scene->cyls[i]))
			scene->valid = false;
		ft_free_string_list(items);
	}
}
