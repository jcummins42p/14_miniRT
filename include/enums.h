/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:05:00 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 14:00:23 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_errcode
{
	SUCCESS,
	ERR_MALLOC,
	ERR_ARGC,
	ERR_ARGV,
	ERR_PARSE,
	ERR_OTHER
};

#endif
