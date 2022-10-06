/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:33:27 by dhubleur          #+#    #+#             */
/*   Updated: 2022/10/06 14:43:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structures.h"
# include "window_props.h"

typedef struct s_params
{
	t_parsing	*parsing;
	t_mlx		*mlx;
}	t_params;

#endif