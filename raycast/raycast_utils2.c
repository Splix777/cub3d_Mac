/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:43:25 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:43:42 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_texture_index(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			game->texture.index = WEST;
		else
			game->texture.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			game->texture.index = SOUTH;
		else
			game->texture.index = NORTH;
	}
}
