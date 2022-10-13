/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:33:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/13 13:27:21 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

# define MALLOC_ERROR "Error\nA malloc failed during parsing"

bool	parse_map(int argc, char **argv, t_parsing *parsing);
bool	parse_double(char *str, double *value);
bool	parse_int(char *str, int *value);
int		get_split_size(char **str);
bool	parse_three_doubles(char *str, double *value1,
			double *value2, double *value3);
bool	parse_three_ints(char *str, int *value1, int *value2, int *value3);
void	free_split(char **elements);
void	free_parse(t_parsing *parsing);
bool	parse_camera(char **args, t_parsing *parsing);
bool	parse_ambient_lightning(char **args, t_parsing *parsing);
bool	parse_light(char **args, t_parsing *parsing);
bool	parse_sphere(char **args, t_parsing *parsing);
bool	parse_plane(char **arg, t_parsing *parsings);
bool	parse_cylinder(char **args, t_parsing *parsing);
bool	parse_textures(char **args, int first, t_texture_infos *texture);
bool	parse_ellipsoid(char **args, t_parsing *parsing);

bool	add_item_to_list(t_generic_object **parsing, void *item,
			t_object_type type);

#endif
