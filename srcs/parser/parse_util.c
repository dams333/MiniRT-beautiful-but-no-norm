/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:19:05 by dhubleur          #+#    #+#             */
/*   Updated: 2022/05/17 12:43:14 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <math.h>

int	get_split_size(char **str)
{
	int length = 0;
	while(str[length] != NULL)
		length++;
	return (length);
}

static bool is_only_digit(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if(!ft_isdigit(str[i]))
			return (false);
	}
	return (true);
}

static bool get_part(char *str, int *value)
{
	if(str == NULL)
	{
		*value = 0;
		return (true);
	}
	if (!is_only_digit(str))
		return (false);
	*value = ft_atoi(str);
	return (true);
}

bool	parse_float(char *str, float *value)
{
	char	**split;
	int		entire;
	int		fractional;
	int		sign;

	sign = 1;
	if(str[0] == '-')
	{
		sign = -1;
		str++;
	}
	split = ft_split(str, '.');
	if (!split)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	if(get_split_size(split) < 1 || get_split_size(split) > 2)
	{
		ft_putstr_fd("Error\nImpossible to parse float: ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	if (!get_part(split[0], &entire) || !get_part(split[1], &fractional))
	{
		ft_putstr_fd("Error\nImpossible to parse float: ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	if (fractional == 0)
		*value = entire;
	else
		*value = entire + (((float) fractional) / ((float) pow(10, ft_strlen(split[1]))));
	*value *= sign;
	return (true);
}

bool	parse_int(char *str, int *value)
{
	int sign;

	sign = 1;
	if(str[0] == '-')
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