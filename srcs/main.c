/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:19:23 by dhubleur          #+#    #+#             */
/*   Updated: 2022/12/09 15:14:49 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parsing.h"
#include "render.h"
#include "window_props.h"
#include "events.h"

bool is_parsing_complete(t_parsing *parsing)
{
	if (parsing->camera == NULL)
	{
		ft_putendl_fd("Error\nPlease specify a camera", 2);
		return (false);
	}
	if (parsing->ambient_lightning == NULL)
	{
		ft_putendl_fd("Error\nPlease specify an ambient lightning", 2);
		return (false);
	}
	return (true);
}

void set_increment(t_params *params)
{
	t_generic_object *obj;
	t_generic_object *dest;

	obj = params->parsing->hittables;
	dest = params->second_map->hittables;
	while (obj)
	{
		t_point *pos;
		t_point *dest_pos;
		t_point *increment;
		int *direction;

		if (obj->type == SPHERE)
		{
			pos = &((t_sphere *)obj->specific_object)->pos;
			increment = &((t_sphere *)obj->specific_object)->coord_increment;
			direction = &((t_sphere *)obj->specific_object)->direction;
			dest_pos = &((t_sphere *)dest->specific_object)->pos;
		}
		else if (obj->type == CYLINDER)
		{
			pos = &((t_cylinder *)obj->specific_object)->pos;
			increment = &((t_cylinder *)obj->specific_object)->coord_increment;
			direction = &((t_cylinder *)obj->specific_object)->direction;
			dest_pos = &((t_cylinder *)dest->specific_object)->pos;
		}
		else if (obj->type == ELLIPSOID)
		{
			pos = &((t_ellipsoid *)obj->specific_object)->pos;
			increment = &((t_ellipsoid *)obj->specific_object)->coord_increment;
			direction = &((t_ellipsoid *)obj->specific_object)->direction;
			dest_pos = &((t_ellipsoid *)dest->specific_object)->pos;
		}
		increment->x = (dest_pos->x - pos->x) / ANIM_UPDATE;
		increment->y = (dest_pos->y - pos->y) / ANIM_UPDATE;
		increment->z = (dest_pos->z - pos->z) / ANIM_UPDATE;
		*direction = 1;

		obj = obj->next;
		dest = dest->next;
	}

	t_generic_object *light = params->parsing->lights;
	t_generic_object *dest_light = params->second_map->lights;
	while (light)
	{
		t_light_object *light_object = (t_light_object *)light->specific_object;
		t_light_object *dest_light_object = (t_light_object *)dest_light->specific_object;
		light_object->coord_increment.x = (dest_light_object->coord_x - light_object->coord_x) / ANIM_UPDATE;
		light_object->coord_increment.y = (dest_light_object->coord_y - light_object->coord_y) / ANIM_UPDATE;
		light_object->coord_increment.z = (dest_light_object->coord_z - light_object->coord_z) / ANIM_UPDATE;
		light_object->direction = 1;

		light = light->next;
		dest_light = dest_light->next;
	}
}

int main(int argc, char **argv)
{
	t_parsing parsing;
	t_parsing second_map;
	t_mlx mlx;
	t_params params;

	parsing.camera = NULL;
	parsing.ambient_lightning = NULL;
	parsing.lights = NULL;
	parsing.hittables = NULL;
	second_map.camera = NULL;
	second_map.ambient_lightning = NULL;
	second_map.lights = NULL;
	second_map.hittables = NULL;
	if (!parse_map(argc, argv, &parsing, &second_map) || !is_parsing_complete(&parsing))
		return (free_parse(&parsing), 1);
	params.parsing = &parsing;
	if (second_map.camera)
	{
		params.second_map = &second_map;
		set_increment(&params);
	}
	else
		params.second_map = NULL;
	if (init_mlx(&mlx) == false)
		return (free_parse(&parsing), 1);
	params.mlx = &mlx;
	params.selected = NULL;
	load_textures(params.mlx, params.parsing);
	init_events(&params);
	render_image(&params);
	mlx_loop(params.mlx->mlx);
	free_textures(&params);
	free_parse(&parsing);
	mlx_destroy_window(params.mlx->mlx, params.mlx->win);
	mlx_destroy_display(params.mlx->mlx);
	free(params.mlx->mlx);
	return (0);
}
