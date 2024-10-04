/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:05:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/04 13:44:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef pthread_mutex_t	t_mutex;

enum e_lock
{
	UNLOCKED,
	LOCKED
};

enum e_coords
{
	_X,
	_Y,
	_Z
};

enum e_rgb
{
	_R,
	_G,
	_B
};

enum e_select_type
{
	SEL_NONE,
	SEL_CAM,
	SEL_SPHERE,
	SEL_PLANE,
	SEL_CYLINDER,
	SEL_LIGHT,
	SEL_LIGHT_VALS,
	SEL_AMBIENT
};

enum e_errcode
{
	SUCCESS,
	ERR_MALLOC,
	ERR_ARGC,
	ERR_ARGV,
	ERR_PARSE,
	ERR_NULLPTR,
	ERR_MLX,
	ERR_OTHER
};

enum e_keypress
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_rescode
{
	RES_FULL = 1,
	RES_HALF,
	RES_QUART,
	RES_EIGHTH,
	RES_SIXNTH,
};

#endif
