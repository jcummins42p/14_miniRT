/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:10:10 by akretov           #+#    #+#             */
/*   Updated: 2024/10/17 20:07:21 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_quaternion	axis_angle_to_quaternion(t_vec3 axis, float angle)
{
	t_quaternion	q;
	float			half_angle;
	float			sin_half_angle;

	half_angle = angle / 2.0;
	sin_half_angle = sin(half_angle);
	q.w = cos(half_angle);
	q.x = axis[_X] * sin_half_angle;
	q.y = axis[_Y] * sin_half_angle;
	q.z = axis[_Z] * sin_half_angle;
	return (q);
}

t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (result);
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	t_quaternion	result;

	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return (result);
}

void	rotate_vector_by_quaternion(t_vec3 vector, t_quaternion q)
{
	t_quaternion	vec_quat;
	t_quaternion	q_conj;
	t_quaternion	result;

	vec_quat.w = 0;
	vec_quat.x = vector[_X];
	vec_quat.y = vector[_Y];
	vec_quat.z = vector[_Z];
	q_conj = quaternion_conjugate(q);
	result = quaternion_multiply(quaternion_multiply(q, vec_quat), q_conj);
	vector[_X] = result.x;
	vector[_Y] = result.y;
	vector[_Z] = result.z;
	vec3_normalize(vector, vector);
}
