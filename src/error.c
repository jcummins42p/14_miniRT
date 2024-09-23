/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:31:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 09:30:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(t_mlx *mlx, char *message, int errcode)
{
	if (mlx)
		cleanup_mlx(mlx);
	while (*message)
		write(2, message++, 1);
	exit (errcode);
}
