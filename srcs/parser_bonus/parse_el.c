/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_el.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:20:00 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/13 13:38:50 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define ELLIPSOID_ERROR_ARGS "Error\nImpossible to parse ellipsoid because \
argument's count is not 4"
#define ELLIPSOID_ERROR_COLOR "Error\nImpossible to parse ellipsoid \
because one of the color composant is not in [0;255]"

bool	parse_ellipsoid_2(char **args, t_ellipsoid *obj, t_parsing *parsing)
{
	if (obj->color_r < 0 || obj->color_r > 255 || obj->color_g < 0
		|| obj->color_g > 255 || obj->color_b < 0 || obj->color_b > 255)
	{
		free(obj);
		return (ft_putendl_fd(ELLIPSOID_ERROR_COLOR, 2), false);
	}
	if (!parse_textures(args, 4, &(obj->texture_infos)))
		return (free(obj), false);
	if (!add_item_to_list(&(parsing->hittables), obj, ELLIPSOID))
	{
		free(obj->texture_infos.normal_map_file);
		free(obj->texture_infos.texture_file);
		return (free(obj), false);
	}
	obj->bump_map.img = NULL;
	return (true);
}

bool	parse_ellipsoid(char **args, t_parsing *parsing)
{
	t_ellipsoid	*obj;

	if (get_split_size(args) != 4 && get_split_size(args) != 6
		&& get_split_size(args) != 8)
		return (ft_putendl_fd(ELLIPSOID_ERROR_ARGS, 2), false);
	obj = ft_calloc(1, sizeof(t_ellipsoid));
	if (!obj)
		return (ft_putendl_fd(MALLOC_ERROR, 2), false);
	if (!parse_three_doubles(args[1], &(obj->pos.x), &(obj->pos.x),
			&(obj->pos.x)))
		return (free(obj), false);
	if (!parse_three_doubles(args[2], &(obj->factors.a),
			&(obj->factors.b), &(obj->factors.c)))
		return (free(obj), false);
	if (!parse_three_ints(args[3], &(obj->color_r), &(obj->color_g),
			&(obj->color_b)))
		return (free(obj), false);
	return (parse_ellipsoid_2(args, obj, parsing));
}
