/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_c_a_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:41:06 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/17 12:46:37 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
}