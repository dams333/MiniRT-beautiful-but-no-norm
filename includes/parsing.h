/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:33:16 by dhubleur          #+#    #+#             */
/*   Updated: 2022/06/27 13:04:58 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

int	parse_map(int argc, char **argv, t_generic_object **lst);
bool	parse_float(char *str, float *value);
bool	parse_int(char *str, int *value);
int		get_split_size(char **str);
bool	parse_three_floats(char *str, float *value1, float *value2, float *value3);
bool	parse_three_ints(char *str, int *value1, int *value2, int *value3);

bool	parse_camera(char **args, t_generic_object **lst);
bool	parse_ambient_lightning(char **args, t_generic_object **lst);
bool	parse_light(char **args, t_generic_object **lst);
bool	parse_sphere(char **args, t_generic_object **lst);
bool	parse_plane(char **arg, t_generic_object **lsts);
bool	parse_cylinder(char **args, t_generic_object **lst);

bool add_item_to_list(t_generic_object **lst, void *item, t_object_type type);

#endif