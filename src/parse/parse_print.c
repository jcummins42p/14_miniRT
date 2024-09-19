/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:59:15 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 21:11:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_sphere(t_sphere sphere)
{
	printf("->Sphere %d:", sphere.id);
	print_vector("\tcenter: ", sphere.center);
	printf("\t\tdiameter: %.2f", sphere.diamtr);
	printf("\t\tcolor: %d\n", sphere.color);
}

void	print_plane(t_plane plane)
{
	printf("->Plane %d:", plane.id);
	print_vector("\tanchor: ", plane.anch);
	print_vector("\t\tnorm: ", plane.anch);
	printf("\tcolor: %d\n", plane.color);
}

void	print_cylinder(t_cylinder cylinder)
{
	printf("->cylinder %d:", cylinder.id);
	print_vector("\tcenter: ", cylinder.center);
	print_vector("\taxis: ", cylinder.axis);
	printf("\tdiameter:%.2f", cylinder.diamtr);
	printf("\theight: %.2f", cylinder.height);
	printf("\tcolor: %d\n", cylinder.color);
}
