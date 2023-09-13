/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:44:27 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:44:51 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = game->ray;
	while (x < game->win_width)
	{
		init_raycast(game, &ray, x);
		set_dda(game, &ray);
		perform_dda(game, &ray);
		get_line_height(game, &ray);
		update_texture_pixels(game, &ray, x);
		x++;
	}
}
