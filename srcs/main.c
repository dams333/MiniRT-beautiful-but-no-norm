/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/07/19 16:45:39 by jmaia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"

int	main(int argc, char **argv)
{
	t_generic_object	*object_list;
	t_mlx				mlx;

	object_list = NULL;
	if (parse_map(argc, argv, &object_list) != 0)
		return (1);
	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);
	mlx_loop(mlx.mlx);
	return (0);
}
