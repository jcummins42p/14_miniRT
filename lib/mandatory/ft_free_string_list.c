/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_string_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:26:52 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 14:37:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_string_list(char **input)
{
	int	i;

	i = 0;
	if (!input || !*input)
		return;
	while(input[i])
		free (input[i++]);
	free (input);
}
