/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:03:36 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 19:14:18 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_final_map(t_game *game)
{
	if (check_map_chars(game) == FALSE)
	{
		printf("CHECK MAP CHARS\n");
		return (FALSE);
	}
	if (check_empty_lines(game) == FALSE)
	{
		printf("CHECK EMPTY LINES\n");
		return (FALSE);
	}
	if (check_map_walls(game) == FALSE)
	{
		printf("CHECK MAP WALLS\n");
		return (FALSE);
	}
	if (check_player(game) == FALSE || check_player_position(game) == FALSE)
	{
		printf("CHECK PLAYER\n");
		return (FALSE);
	}
	return (TRUE);
}

void	find_finalmap_dimensions(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map[i])
	{
		while (game->map.map[i][0] == '\n' || ft_isalpha(game->map.map[i][0]))
			i++;
		while (game->map.map[i] && (game->map.map[i][0] == '1' || game->map.map[i][0] == ' '))
		{
			game->map.height++;
			i++;
		}
		while(game->map.map[i])
		{
			if (game->map.map[i][0] != '\n')
				game->map.height = 0;
			i++;
		}
	}
}

int	check_validate_map(t_game *game)
{
	int	i;
	int	j;

	find_finalmap_dimensions(game);
	if (game->map.height < 3)
		return (err_msg(INVMAP, 0));
	game->f_map = ft_calloc(game->map.height + 1, sizeof(char *));
	if (game->f_map == NULL)
		return (err_msg(MALLOCFAIL, 0));
	i = 0;
	j = 0;
	while (game->map.map && game->map.map[j])
	{
		if (game->map.map[j][0] == '1' || game->map.map[j][0] == ' ')
		{
			game->f_map[i] = rem_nl(game->map.map[j]);
			i++;
		}
		j++;
	}
	game->f_map[i] = NULL;
	if (validate_final_map(game) == FALSE)
		return (FALSE);
	else
		return (TRUE);
}

int	check_validate_map_order(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map && game->map.map[i])
	{
		if (game->map.map[i][0] == '1' || game->map.map[i][0] == ' ')
			break ;
		i++;
	}
	while (game->map.map && game->map.map[i])
	{
		if (game->map.map[i][0] == '\0' || ft_isalpha(game->map.map[i][0]))
			return (err_msg(MAPORDER, 0));
		i++;
	}
	return (TRUE);
}
