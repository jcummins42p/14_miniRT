/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:05:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 16:35:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# define DEBUGMODE 1

enum e_errcode
{
	SUCCESS,
	ERR_MALLOC,
	ERR_ARGC,
	ERR_ARGV,
	ERR_PARSE,
	ERR_NULLPTR,
	ERR_OTHER
};

#endif
