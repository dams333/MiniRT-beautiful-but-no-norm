/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaia <jmaia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:16:28 by jmaia             #+#    #+#             */
/*   Updated: 2022/10/10 17:21:26 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

typedef struct s_checkerboard
{
	int	height;
	int	width;
	int	color_r;
	int	color_g;
	int	color_b;
}	t_checkerboard;

#endif
