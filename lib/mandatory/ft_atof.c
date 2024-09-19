/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:12:41 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 13:48:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

float	atof_calculate(char *input, int sign, int divisor, bool in_fraction)
{
	double	int_side;
	double	dec_side;

	int_side = 0.0;
	dec_side = 0.0;
	while (*input)
	{
		if (*input >= '0' && *input <= '9')
		{
			if (!in_fraction)
				int_side = int_side * 10 + (*input - '0');
			else
			{
				dec_side = dec_side * 10 + (*input - '0');
				divisor *= 10;
			}
		}
		else if (*input == '.' && !in_fraction)
			in_fraction = true;
		else
			return (sign * (int_side + (dec_side / divisor)));
		input++;
	}
	return (sign * (int_side + (dec_side / divisor)));
}

float	ft_atof(char *input)
{
	float	output;
	int		sign;
	int		divisor;
	bool	in_fraction;

	output = 0.0;
	divisor = 1;
	sign = 1;
	in_fraction = false;
	if (!input || !*input)
		return (output);
	if (*input == '-')
	{
		input++;
		sign = -1;
	}
	output = atof_calculate(input, sign, divisor, in_fraction);
	return (output);
}

/*int	main(void)*/
/*{*/
	/*float	test2 = -1234.4321;*/
	/*char *test = "-1234.4321";*/
	/*printf("%s as float is %f, should be %f\n", test, ft_atof(test), test2);*/
	/*return(0);*/
/*}*/
