/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:58:24 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 17:05:40 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <math.h>
# include <mlx.h>
//# include <X11/keysym.h>
//# include <X11/keysymdef.h>
# include <X11/X.h>
# include <X11/XKBlib.h>

// forbidden threading functions - remove before evaluation!
# include <pthread.h>

# include "defines.h"
# include "XK_defines.h"
# include "enums.h"
# include "structs.h"

# include "funcs_utils.h"
# include "funcs_control.h"
# include "funcs_draw.h"
# include "funcs_intersect.h"
# include "funcs_maths.h"
# include "funcs_parse.h"
# include "funcs_print.h"
# include "funcs_misc.h"

#endif
