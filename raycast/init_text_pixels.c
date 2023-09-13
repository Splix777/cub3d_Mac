/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_pixels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:39:17 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:39:37 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_texture_pixels(t_game *game)
{
	int	i;

	if (game->texture_pixels != NULL)
		free_void_array((void **)game->texture_pixels);
	game->texture_pixels = ft_calloc(game->win_height + 1, sizeof(int *));
	if (game->texture_pixels == NULL)
		free_exit(game, 1);
	i = 0;
	while (i < game->win_height)
	{
		game->texture_pixels[i] = ft_calloc(game->win_width + 1, sizeof(int *));
		if (game->texture_pixels[i] == NULL)
			free_exit(game, 1);
		i++;
	}
}
