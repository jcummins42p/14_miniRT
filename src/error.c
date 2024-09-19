/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:31:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 10:50:17 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(char *message, int errcode)
{
	while (*message)
		write(2, message++, 1);
	write(2, "\n", 1);
	exit (errcode);
}
