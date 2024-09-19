/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:35:02 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 19:14:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

void	set_vector(t_vector vec, char *input);
int		set_colors(char *input);

//	parse.c
void	parse(int *fd, int argc, t_scene **scenes);

//	error.c
void	exit_error(char *message, int errcode);

#endif
