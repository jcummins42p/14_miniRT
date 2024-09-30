/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:58:24 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/30 14:35:54 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/X.h>
# include <X11/XKBlib.h>

// forbidden threading functions - remove before evaluation!
# include <pthread.h>

# include "defines.h"
# include "enums.h"
# include "structs.h"
# include "funcs.h"

# define XK_KP_0	0xffb0
# define XK_KP_1	0xffb1
# define XK_KP_2	0xffb2
# define XK_KP_3	0xffb3
# define XK_KP_4	0xffb4
# define XK_KP_5	0xffb5
# define XK_KP_6	0xffb6
# define XK_KP_7	0xffb7
# define XK_KP_8	0xffb8
# define XK_KP_9	0xffb9

# define XK_KP_Subtract	0xffad
# define XK_KP_Add		0xffab

#endif
