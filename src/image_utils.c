/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:26 by vdenisse          #+#    #+#             */
/*   Updated: 2024/02/29 14:50:31 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	check_info(t_drawing *d)
{
	if (!d->tex[NO].img)
		return (1);
	if (!d->tex[SO].img)
		return (1);
	if (!d->tex[EA].img)
		return (1);
	if (!d->tex[WE].img)
		return (1);
	return (0);
}

void	set_drawing_to_null(t_drawing *d)
{
	d->tex[NO].img = 0;
	d->tex[SO].img = 0;
	d->tex[WE].img = 0;
	d->tex[EA].img = 0;
}
