/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp_pl_cy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:26:02 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/18 10:31:20 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_sphere(char **args)
{
	t_sphere_object *obj;
	
	if(get_split_size(args) != 4)
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
	if(obj->diameter < 0)
	{
		ft_putendl_fd("Error\nImpossible to parse sphere because diameter is < 0", 2);
		return (false);
	}
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g), &(obj->color_b)))
		return (false);
	if(obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0 || obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		ft_putendl_fd("Error\nImpossible to parse sphere because one of the color composant in not in [0;255]", 2);
		return (false);
	}
	free(obj);
	return (true);
}