/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_c_a_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:41:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/17 13:44:37 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_three_floats(char *str, float *value1, float *value2, float *value3)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (get_split_size(split) != 3)
	{
		ft_putendl_fd("Error\nImpossible to parse 3 floats comma separated", 2);
		return (false);
	}
	if(!parse_float(split[0], value1))
		return (false);
	if(!parse_float(split[1], value2))
		return (false);
	if(!parse_float(split[2], value3))
		return (false);
	return (true);
}

bool	parse_camera(char **args)
{
	t_camera_object *obj;
	
	if(get_split_size(args) != 4)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because argument's count is not 4", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(obj));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
		return (false);
	if (!parse_three_floats(args[2], &(obj->orientation_x), &(obj->orientation_y), &(obj->orientation_z)))
		return (false);
	if(obj->orientation_x < -1 || obj->orientation_x > 1 || obj->orientation_y < -1 || obj->orientation_y > 1 || obj->orientation_z < -1 || obj->orientation_z > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because orientation vector is not normalized", 2);
		return (false);
	}
	if (!parse_int(args[3], &(obj->horizontal_fov)))
		return (false);
	if(obj->horizontal_fov < 0 || obj->horizontal_fov > 180)
	{
		ft_putendl_fd("Error\nImpossible to parse camera because FOV is not in [0;180]", 2);
		return (false);
	}
	free(obj);
	return (true);
}