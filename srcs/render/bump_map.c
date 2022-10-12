/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:18:39 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/12 15:00:01 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "checkerboard.h"
#include "mlx.h"

t_texture	load_map(t_mlx *mlx, char *file)
{
	t_texture	texture;
	void		*img;
	int			unused;

	texture.data = NULL;
	img = mlx_xpm_file_to_image(mlx->mlx, file, &(texture.width),
			&(texture.height));
	if (img == NULL)
		return (texture);
	texture.data = (int *)mlx_get_data_addr(img, &unused, &unused, &unused);
	return (texture);
}

void	perturb_normal(t_params *params, t_obj_intersection intersection,
	t_vector *normal)
{
	static t_texture	texture = {NULL, 0, 0};
	t_point2d			board_pos;
	int					map_color;
	float				gray_scale;

	if (texture.data == NULL)
		texture = load_map(params->mlx, "bump_map.xpm");
	if (texture.data == NULL)
		return ;
	board_pos = to_checkerboard_pos(intersection.intersected,
			intersection.intersection);
	printf("Sphere pos: %f, %f, %f\n", ((t_sphere *)intersection.intersected->specific_object)->pos.x, ((t_sphere *)intersection.intersected->specific_object)->pos.y, ((t_sphere *)intersection.intersected->specific_object)->pos.z);
	printf("Intersection pos: %f, %f, %f\n", intersection.intersection.x,
		intersection.intersection.y, intersection.intersection.z);
	printf("Board pos: %f %f\n", board_pos.x, board_pos.y);
	board_pos.x = (int)(board_pos.x * texture.width) % texture.width;
	board_pos.y = (int)(board_pos.y * texture.height) % texture.height;
	printf("Texture pos: %.0f %.0f (limits: %i %i)\n", board_pos.x, board_pos.y, texture.width, texture.height);
	map_color = texture.data[(int)(board_pos.y * texture.width + board_pos.x)];
	map_color = (map_color & 0xFF0000) >> 16;
	gray_scale = (float)map_color / 255.0;
	normal->x += (1 - gray_scale) * normal->x + gray_scale;
	normal->y += (1 - gray_scale) * normal->y + gray_scale;
	normal->z += (1 - gray_scale) * normal->z + gray_scale;
	normalize(normal);
}
