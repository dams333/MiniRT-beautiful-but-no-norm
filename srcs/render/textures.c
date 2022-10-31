/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:18:39 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/31 12:54:50 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "checkerboard.h"
#include "mlx.h"

t_texture	load_texture(t_mlx *mlx, char *file)
{
	t_texture	texture;
	int			unused;

	texture.data = NULL;
	if (file != NULL)
	{
		texture.img = mlx_xpm_file_to_image(mlx->mlx, file, &(texture.width),
				&(texture.height));
		if (texture.img == NULL)
			return (texture);
		texture.data = (int *)mlx_get_data_addr(texture.img,
				&unused, &unused, &unused);
	}
	return (texture);
}

void	extract_texture(t_generic_object *obj, t_texture **normal_map,
	t_texture **texture, t_texture_infos *texture_infos)
{
	if (obj->type == SPHERE)
	{
		*normal_map = &(((t_sphere *)obj->specific_object)->bump_map);
		*texture = &(((t_sphere *)obj->specific_object)->texture);
		*texture_infos = ((t_sphere *)obj->specific_object)->texture_infos;
	}
	else if (obj->type == PLANE)
	{
		*normal_map = &(((t_plane *)obj->specific_object)->bump_map);
		*texture = &(((t_plane *)obj->specific_object)->texture);
		*texture_infos = ((t_plane *)obj->specific_object)->texture_infos;
	}
	else if (obj->type == CYLINDER)
	{
		*normal_map = &(((t_cylinder *)obj->specific_object)->bump_map);
		*texture = &(((t_cylinder *)obj->specific_object)->texture);
		*texture_infos = ((t_cylinder *)obj->specific_object)->texture_infos;
	}
	else
	{
		*normal_map = &(((t_ellipsoid *)obj->specific_object)->bump_map);
		*texture = &(((t_ellipsoid *)obj->specific_object)->texture);
		*texture_infos
			= ((t_ellipsoid *)obj->specific_object)->texture_infos;
	}
}

void	load_textures(t_mlx *mlx, t_parsing *parsing)
{
	t_generic_object	*obj;
	t_texture			*texture;
	t_texture			*normal_map;
	t_texture_infos		infos;

	obj = parsing->hittables;
	while (obj)
	{
		extract_texture(obj, &normal_map, &texture, &infos);
		if (infos.texture_file != NULL)
			*texture = load_texture(mlx, infos.texture_file);
		if (infos.normal_map_file != NULL)
			*normal_map = load_texture(mlx, infos.normal_map_file);
		obj = obj->next;
	}
}

void	free_textures(t_params *params)
{
	t_generic_object	*obj;
	t_texture			*texture;
	t_texture			*normal_map;
	t_texture_infos		infos;

	obj = params->parsing->hittables;
	while (obj)
	{
		extract_texture(obj, &normal_map, &texture, &infos);
		if (normal_map->img != NULL)
			mlx_destroy_image(params->mlx->mlx, normal_map->img);
		if (texture->img != NULL)
			mlx_destroy_image(params->mlx->mlx, texture->img);
		obj = obj->next;
	}
}

void	load_texture_color(float c[3], t_generic_object *intersected,
	t_point intersection, int is_cap)
{
	t_texture			*texture;
	t_texture			*normal_map;
	t_texture_infos		infos;
	t_point2d			board_pos;
	int					map_color;

	extract_texture(intersected, &normal_map, &texture, &infos);
	if (texture->img != NULL)
	{
		board_pos = to_checkerboard_pos(intersected, intersection, is_cap);
		board_pos.x *= (board_pos.x < 0) * -1 + (board_pos.x >= 0) * 1;
		board_pos.y *= (board_pos.y < 0) * -1 + (board_pos.y >= 0) * 1;
		board_pos.x = (int)(board_pos.x * texture->width) % texture->width;
		board_pos.y = (int)(board_pos.y * texture->height) % texture->height;
		map_color
			= texture->data[(int)(board_pos.y * texture->width + board_pos.x)];
		c[0] = (double)((map_color & 0xFF0000) >> 16) / 255.0;
		c[1] = (double)((map_color & 0xFF00) >> 8) / 255.0;
		c[2] = (double)((map_color & 0xFF)) / 255.0;
	}
	if (infos.checkerboard.height > 0)
		load_checkerboard_color(c, infos.checkerboard,
			(t_generic_object_metaed){.obj = intersected, .is_cap = is_cap},
			intersection);
}
