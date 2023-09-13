/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:45:25 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:45:50 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_frame(t_game *game)
{
	init_texture_pixels(game);
	init_ray(&game->ray);
	raycast(game);
	draw_frame(game);
}

int	render(t_game *game)
{
	game->player.has_moved += move_player(game);
	if (game->player.has_moved == 0)
		return (0);
	render_frame(game);
	return (0);
}
