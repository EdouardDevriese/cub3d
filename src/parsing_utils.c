/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:56:03 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/06 15:29:36 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *str)
{
	bool	has_info;

	has_info = false;
	while (*str && *str != '\n')
	{
		if (*str != '1' && *str != ' ' && *str != '0')
			return (0);
		if (*str == '1' || *str == '0')
			has_info = true;
		str++;
	}
	return (has_info);
}
