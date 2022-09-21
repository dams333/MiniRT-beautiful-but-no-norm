/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:56:45 by dhubleur          #+#    #+#             */
/*   Updated: 2022/09/21 18:12:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	add_item_to_list(t_generic_object **lst, void *item, t_object_type type)
{
	t_generic_object	*generic_item;
	t_generic_object	*tmp;

	generic_item = malloc(sizeof(t_generic_object));
	if (!generic_item)
	{
		ft_putendl_fd("Error\nA malloc failed during parsing", 2);
		return (false);
	}
	generic_item->type = type;
	generic_item->specific_object = item;
	generic_item->next = NULL;
	if (!(*lst))
		*lst = generic_item;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = generic_item;
	}
	return (true);
}
