/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:34:52 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/19 14:04:23 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	valid_texture(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (array_size(split) != 2)
	{
		free_char_array(split);
		return (FALSE);
	}
	if (!ft_strcmp(split[0], "NO") && !ft_strcmp(split[0], "SO")
		&& !ft_strcmp(split[0], "WE") && !ft_strcmp(split[0], "EA"))
	{
		free_char_array(split);
		return (FALSE);
	}
	if (ext_check_xpm(split[1]))
	{
		free_char_array(split);
		return (TRUE);
	}
	free_char_array(split);
	return (FALSE);
}

int	already_filled(char *line, t_game *game)
{
	if (!ft_strncmp(line, "NO", 2) && game->texture.north != NULL)
	{
		free (game->texture.north);
		return (false);
	}
	if (!ft_strncmp(line, "SO", 2) && game->texture.south != NULL)
	{
		free (game->texture.south);
		return (false);
	}
	if (!ft_strncmp(line, "WE", 2) && game->texture.west != NULL)
	{
		free (game->texture.west);
		return (false);
	}
	if (!ft_strncmp(line, "EA", 2) && game->texture.east != NULL)
	{
		free (game->texture.east);
		return (false);
	}
	return (true);
}

char	*get_text(char *line, t_game *game)
{
	char	**split;
	char	*text;

	if (!already_filled(line, game))
	{
		game->texture.texture_count++;
		return (NULL);
	}
	if (valid_texture(line) == FALSE)
	{
		game->texture.texture_count++;
		return (NULL);
	}
	split = ft_split(line, ' ');
	text = rem_nl(split[1]);
	free_char_array(split);
	game->texture.texture_count++;
	return (text);
}

int	check_validate_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->map.map && game->map.map[i])
	{
		if (!ft_strncmp(game->map.map[i], "NO", 2))
			game->texture.north = get_text(game->map.map[i], game);
		else if (!ft_strncmp(game->map.map[i], "SO", 2))
			game->texture.south = get_text(game->map.map[i], game);
		else if (!ft_strncmp(game->map.map[i], "WE", 2))
			game->texture.west = get_text(game->map.map[i], game);
		else if (!ft_strncmp(game->map.map[i], "EA", 2))
			game->texture.east = get_text(game->map.map[i], game);
		i++;
	}
	if (game->texture.north == NULL || game->texture.south == NULL
		|| game->texture.west == NULL || game->texture.east == NULL
		|| game->texture.texture_count != 4)
		return (err_msg(INVTEXTURE, FALSE));
	else
		return (TRUE);
}
