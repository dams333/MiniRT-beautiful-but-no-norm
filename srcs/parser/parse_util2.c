/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:19:32 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/10 14:49:21 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include "structures.h"

int		get_split_size(char **str);
void	free_split(char **elements);
void	free_parse(t_parsing *parsing);
bool	is_only_digit(char *str);
bool	get_part(char *str, int *value);

bool	split_error(char **split, char *str, int *entire, int *fractional)
{
	if (get_split_size(split) < 1 || get_split_size(split) > 2)
	{
		ft_putstr_fd("Error\nImpossible to parse float: ", 2);
		ft_putendl_fd(str, 2);
		free_split(split);
		return (false);
	}
	if (!get_part(split[0], entire) || !get_part(split[1], fractional))
	{
		ft_putstr_fd("Error\nImpossible to parse float: ", 2);
		ft_putendl_fd(str, 2);
		free_split(split);
		return (false);
	}
	return (true);
}

bool	parse_double(char *str, double *value)
{
	char	**split;
	int		entire;
	int		fractional;
	int		sign;

	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	split = ft_split(str, '.');
	if (!split)
		return (ft_putendl_fd("Error\nA malloc failed during parsing", 2),
			false);
	if (!split_error(split, str, &entire, &fractional))
		return (false);
	if (fractional == 0)
		*value = entire;
	else
		*value = entire + (((double) fractional)
				/ ((double) pow(10, ft_strlen(split[1]))));
	*value *= sign;
	free_split(split);
	return (true);
}

bool	parse_int(char *str, int *value)
{
	int	sign;

	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	if (!is_only_digit(str))
	{
		ft_putstr_fd("Error\nImpossible to parse int: ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	*value = ft_atoi(str);
	*value *= sign;
	return (true);
}

bool	parse_three_doubles(char *str, double *value1,
			double *value2, double *value3)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Error\nA malloc failed during parsing", 2),
			false);
	if (get_split_size(split) != 3)
	{
		ft_putendl_fd("Error\nImpossible to parse 3 floats comma separated", 2);
		return (free_split(split), false);
	}
	if (!parse_double(split[0], value1))
		return (free_split(split), false);
	if (!parse_double(split[1], value2))
		return (free_split(split), false);
	if (!parse_double(split[2], value3))
		return (free_split(split), false);
	free_split(split);
	return (true);
}

bool	parse_three_ints(char *str, int *value1,
			int *value2, int *value3)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Error\nA malloc failed during parsing", 2),
			false);
	if (get_split_size(split) != 3)
	{
		ft_putendl_fd("Error\nImpossible to parse 3 ints comma separated", 2);
		return (free_split(split), false);
	}
	if (!parse_int(split[0], value1))
		return (free_split(split), false);
	if (!parse_int(split[1], value2))
		return (free_split(split), false);
	if (!parse_int(split[2], value3))
		return (free_split(split), false);
	free_split(split);
	return (true);
}
