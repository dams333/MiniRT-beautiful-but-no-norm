/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_filled.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:32:05 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/10 17:38:42 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "checkerboard.h"

int	is_filled(t_checkerboard checkerboard, double x, double y)
{
	int	check_x;
	int	check_y;

	check_x = x * checkerboard.width;
	check_y = y * checkerboard.height;
	return ((check_x + check_y) % 2);
}
