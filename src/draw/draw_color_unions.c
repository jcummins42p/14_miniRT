/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_unions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:11:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/15 10:41:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_col	color_invert_u(t_col input)
{
	t_col	output;

	output.c[_R] = 255 - input.c[_R];
	output.c[_G] = 255 - input.c[_G];
	output.c[_B] = 255 - input.c[_B];
	return (output);
}

//	for direct light illuminating a color?
t_col	color_illuminate_u(t_col in, t_col light, float ratio)
{
	t_col	out;

	if (ratio < 0)
		ratio = 0;
	else if (ratio > 1)
		ratio = 1;
	out.c[0] = fmin(fmax(0, (in.c[0] * (int)((light.c[0] / 255) * ratio))), 255);
	out.c[1] = fmin(fmax(0, (in.c[1] * (int)((light.c[1] / 255) * ratio))), 255);
	out.c[2] = fmin(fmax(0, (in.c[2] * (int)((light.c[2] / 255) * ratio))), 255);
	return (out);
}

t_col	color_subtract_u(t_col in, t_col sub, float ratio)
{
	t_col	out;

	if (ratio <= 0)
		return (in);
	else if (ratio >= 1)
		ratio = 1;
	out.c[_R] = fmin(fmax(0, (in.c[0] - (int)(sub.c[_R] * ratio))), 255);
	out.c[_G] = fmin(fmax(0, (in.c[1] - (int)(sub.c[_G] * ratio))), 255);
	out.c[_B] = fmin(fmax(0, (in.c[2] - (int)(sub.c[_B] * ratio))), 255);
	return (out);
}

t_col	color_addition_u(t_col in, t_col add)
{
	t_col	out;

	out.c[0] = fmin(fmax(0, (in.c[0] + add.c[0])), 255);
	out.c[1] = fmin(fmax(0, (in.c[1] + add.c[1])), 255);
	out.c[2] = fmin(fmax(0, (in.c[2] + add.c[2])), 255);
	return (out);
}

//	shifts 'original' to 'target' by a ratio: 0 is all original, 1 is all target
t_col	color_shift_u(t_col a, t_col b, float ratio)
{
	t_col	out;

	if (ratio < 0)
		return (a);
	else if (ratio > 1)
		return (b);
	out.c[0] = fmin(fmax(0, (a.c[0] + (int)((b.c[0] - a.c[0]) * ratio))), 255);
	out.c[1] = fmin(fmax(0, (a.c[1] + (int)((b.c[1] - a.c[1]) * ratio))), 255);
	out.c[2] = fmin(fmax(0, (a.c[2] + (int)((b.c[2] - a.c[2]) * ratio))), 255);
	return (out);
}
