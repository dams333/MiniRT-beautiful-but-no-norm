/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp_pl_cy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:26:02 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/22 22:25:40 by jmaia            ###   ###               */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_sphere(char **args, t_generic_object **lst)
{
	t_sphere_object *obj;
	
	if (get_split_size(args) != 4)
	{
		ft_putendl_fd("Error\nImpossible to parse sphere because argument's count is not 4", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_sphere_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
		return (false);
	if (!parse_float(args[2], &(obj->diameter)))
		return (false);
	if (obj->diameter < 0)
	{
		ft_putendl_fd("Error\nImpossible to parse sphere because diameter is < 0", 2);
		return (false);
	}
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
		return (false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse sphere because one of the color composant in not in [0;255]", 2);
		return (false);
	}
	if (!add_item_to_list(lst, obj, CAMERA))
		return (false);
	return (true);
}

bool	parse_plane(char **args, t_generic_object **lst)
{
	t_plane_object *obj;
	
	if (get_split_size(args) != 4)
	{
		ft_putendl_fd("Error\nImpossible to parse plane because argument's count is not 4", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_plane_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
		return (false);
	if (!parse_three_floats(args[2], &(obj->orientation_x), &(obj->orientation_y), &(obj->orientation_z)))
		return (false);
	if (obj->orientation_x < -1 || obj->orientation_x > 1 || obj->orientation_y < -1 || obj->orientation_y > 1 || obj->orientation_z < -1 || obj->orientation_z > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse plane because one composant of the orientation vector is not in [-1;1]", 2);
		return (false);
	}
	obj->d = -obj->orientation_x * obj->coord_x - obj->orientation_y * obj->coord_y - obj->orientation_z * obj->coord_z;
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
		return (false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse plane because one of the color composant in not in [0;255]", 2);
		return (false);
	}
	if (!add_item_to_list(lst, obj, CAMERA))
		return (false);
	return (true);
}

bool	parse_cylinder(char **args, t_generic_object **lst)
{
	t_cylinder_object *obj;
	
	if (get_split_size(args) != 6)
	{
		ft_putendl_fd("Error\nImpossible to parse cylinder because argument's count is not 6", 2);
		return (false);
	}
	obj = ft_calloc(1, sizeof(t_cylinder_object));
	if (!obj)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if (!parse_three_floats(args[1], &(obj->coord_x), &(obj->coord_y), &(obj->coord_z)))
		return (false);
	if (!parse_three_floats(args[2], &(obj->orientation_x), &(obj->orientation_y), &(obj->orientation_z)))
		return (false);
	if (obj->orientation_x < -1 || obj->orientation_x > 1 || obj->orientation_y < -1 || obj->orientation_y > 1 || obj->orientation_z < -1 || obj->orientation_z > 1)
	{
		ft_putendl_fd("Error\nImpossible to parse cylinder because one composant of the orientation vector is not in [-1;1]", 2);
		return (false);
	}
	if (!parse_float(args[3], &(obj->diameter)))
		return (false);
	if (obj->diameter < 0)
	{
		ft_putendl_fd("Error\nImpossible to parse cylinder because diameter is < 0", 2);
		return (false);
	}
	if (!parse_float(args[4], &(obj->height)))
		return (false);
	if (obj->height < 0)
	{
		ft_putendl_fd("Error\nImpossible to parse cylinder because height is < 0", 2);
		return (false);
	}
	if (!parse_three_ints(args[5], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
		return (false);
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse cylinder because one of the color composant in not in [0;255]", 2);
		return (false);
	}
	if (!add_item_to_list(lst, obj, CAMERA))
		return (false);
	return (true);
}
