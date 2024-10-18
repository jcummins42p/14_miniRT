/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 14:35:29 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_color(char *input) // assumes csv RGB
{
	char	**items;
	int		color;

	color = 0;
	items = NULL;
	if (!input)
		return (0);
	items = ft_split(input, ',');
	if (!items || !items[0] || !items[1] || !items[2])
	{
		printf("Malloc error setting color: initialize %s to zero\n", input);
		return (0);
	}
	printf("%s, %s, %s\n", items[0], items[1], items[2]);
	color += ft_atoi(items[0]) << 16;
	color += ft_atoi(items[1]) << 8;
	color += ft_atoi(items[2]);
	ft_free_string_list(items);
	return (color);
}

void	zero_vec3(t_vec3 vec)
{
	int	i;

	i = 0;
	while (i < 3)
		vec[i++] = 0.0;
}

int	set_vec3(t_vec3 vec, char *input)
{
	char	**items;
	int		i;

	i = -1;
	items = NULL;
	if (!input || !*input)
		return (1);
	items = ft_split(input, ',');
	if (!items)
	{
		printf("Malloc error setting vector: initialize %s to zero\n", input);
		while (++i < 3)
			vec[i] = 0;
		return (1);
	}
	while (++i < 3)
		vec[i] = ft_atof(items[i]);
	ft_free_string_list(items);
	return (0);
}

int	set_unit_vec3(t_vec3 vec, char *input)
{
	float	error;

	error = 1.0;
	if (set_vec3(vec, input))
		return (1);
	error = fl_abs(1 - vec3_length(vec));
	if (error > EPSILON)
	{
		printf("Error: Invalid unit vector input\n");
		return (1);
	}
	return (0);
}
