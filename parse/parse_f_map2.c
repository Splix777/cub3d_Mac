/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:25:46 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:28:18 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (game->f_map == NULL)
		return (FALSE);
	while (game->f_map[i])
	{
		j = 0;
		while (game->f_map[i][j])
		{
			if (!ft_strchr("01NSEW ", game->f_map[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	check_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->f_map[i])
	{
		j = 0;
		while (game->f_map[i][j])
		{
			if (ft_strchr("NSEW", game->f_map[i][j]))
			{
				game->player.player_count++;
				game->player.pos_x = (double)j + 0.5;
				game->player.pos_y = (double)i + 0.5;
				game->player.dir = game->f_map[i][j];
				game->f_map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (game->player.player_count != 1)
		return (FALSE);
	return (TRUE);
}

int	check_player_position(t_game *game)
{
	int	row;
	int	col;

	row = (int)(game->player.pos_y);
	col = (int)(game->player.pos_x);
	if (game->f_map[row][(col + 1)] == '\0'
		|| game->f_map[row][(col + 1)] == ' '
		|| (col > 0 && game->f_map[row][(col - 1)] == ' '))
		return (FALSE);
	return (TRUE);
}

int	check_empty_lines(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->f_map[i])
	{
		j = 0;
		if (game->f_map[i][0] == '\0')
			return (FALSE);
		while (game->f_map[i][j] && game->f_map[i][j] == ' ')
		{
			if (game->f_map[i][j + 1] == '\0')
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}
