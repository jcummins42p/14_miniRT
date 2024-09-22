/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/22 09:52:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_color(char *input) // assumes csv RGB
{
	char	**items;
	int		color;

	color = 0;
	items = NULL;
	if (!input || !input[0] || !input[1] || !input[2])
		return (0);
	items = ft_split(input, ',');
	color += ft_atoi(items[0]) << 16;
	color += ft_atoi(items[1]) << 8;
	color += ft_atoi(items[2]);
	ft_free_string_list(items);
	return (color);
}

void	zero_vector(t_vector vec)
{
	int	i;

	i = 0;
	while (i < 3)
		vec[i++] = 0.0;
}

void	set_vector(t_vector vec, char *input)
{
	char		**items;
	int			i;

	i = -1;
	items = NULL;
	if (!input || !*input)
		return ;
	items = ft_split(input, ',');
	while (++i < 3)
		vec[i] = ft_atof(items[i]);
	ft_free_string_list(items);
}
