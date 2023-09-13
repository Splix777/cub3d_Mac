/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:44 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:19:25 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valid_pos(t_game *game, double x, double y)
{
	if (x < 0.25 || x >= game->map.width - 1.25
		|| y < 0.25 || y >= game->map.height - 0.25)
	{
		return (FALSE);
	}
	if (game->f_map[(int)y][(int)x] == '0')
	{
		return (TRUE);
	}
	return (FALSE);
}

int	check_movement(t_game *game, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(game, new_x, game->player.pos_y))
	{
		game->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(game, game->player.pos_x, new_y))
	{
		game->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
