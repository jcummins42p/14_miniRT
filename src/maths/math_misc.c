/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:04:13 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 19:32:44 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	toggle_bool(bool *current)
{
	if (*current)
		*current = false;
	else
		*current = true;
}

float	fl_abs(float f)
{
	if (f < 0)
		f = -f;
	return (f);
}
