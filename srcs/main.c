/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/21 17:40:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "events.h"
#include "parsing.h"
#include "window_props.h"

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_mlx		mlx;

	parsing.camera = NULL;
	parsing.ambient_lightning = NULL;
	parsing.lights = NULL;
	parsing.hittables = NULL;
	if (parse_map(argc, argv, &parsing) == false)
	{
		//TODO free_parse(parsing)
		return (1);
	}
	if (!init_mlx(&mlx))
		return (1);
	init_events(mlx.mlx, mlx.win);
	mlx_loop(mlx.mlx);
	return (0);
}
