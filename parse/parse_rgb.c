/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:29:10 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/21 12:13:16 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned long	rgb_to_hex(t_game *game, char *type)
{
	unsigned long	hex;

	if (!ft_strcmp(type, "F"))
		hex = ((game->texture.floor.r & 0xff) << 16)
			| ((game->texture.floor.g & 0xff) << 8)
			| (game->texture.floor.b & 0xff);
	else if (!ft_strcmp(type, "C"))
		hex = ((game->texture.ceiling.r & 0xff) << 16)
			| ((game->texture.ceiling.g & 0xff) << 8)
			| (game->texture.ceiling.b & 0xff);
	else
		hex = 0;
	return (hex);
}

int	load_rgb(t_game *game, char **rgb, char *type)
{
	int	i;
	int	color;

	i = 0;
	while (rgb[i])
	{
		color = ft_atoi(rgb[i]);
		if (color < 0 || color > 255 || !ft_isdigit(rgb[i][0]))
			return (FALSE);
		i++;
	}
	if (!ft_strcmp(type, "F"))
	{
		game->texture.floor.r = ft_atoi(rgb[0]);
		game->texture.floor.g = ft_atoi(rgb[1]);
		game->texture.floor.b = ft_atoi(rgb[2]);
	}
	if (!ft_strcmp(type, "C"))
	{
		game->texture.ceiling.r = ft_atoi(rgb[0]);
		game->texture.ceiling.g = ft_atoi(rgb[1]);
		game->texture.ceiling.b = ft_atoi(rgb[2]);
	}
	return (TRUE);
}

int	valid_rgb(t_game *game, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if ((array_size(split) != 2) || (split[0][1] != '\0'))
	{
		free_char_array(split);
		return (FALSE);
	}
	rgb = ft_split(split[1], ',');
	if ((array_size(rgb) != 3) || !load_rgb(game, rgb, split[0]))
	{
		free_char_array(split);
		free_char_array(rgb);
		return (FALSE);
	}
	free_char_array(split);
	free_char_array(rgb);
	return (TRUE);
}

int	get_rgb(t_game *game, char *line)
{
	if (valid_rgb(game, line) == FALSE)
		return (-1);
	if (line[0] == 'F')
		game->texture.f_count++;
	if (line[0] == 'C')
		game->texture.c_count++;
	return (TRUE);
}

int	check_validate_rgb(t_game *game)
{
	int	i;
	int	loaded;

	i = 0;
	loaded = 0;
	while (game->map.map[i])
	{
		if (game->map.map[i][0] == 'F' || game->map.map[i][0] == 'C')
		{
			if (get_rgb(game, game->map.map[i]) == -1)
				return (err_msg(INVRGB, FALSE));
			loaded++;
		}
		i++;
	}
	game->texture.rgb_count = loaded;
	game->texture.hex_ceiling = rgb_to_hex(game, "C");
	game->texture.hex_floor = rgb_to_hex(game, "F");
	if (loaded != 2 || comma_count(game) == FALSE
		|| game->texture.f_count != 1 || game->texture.c_count != 1)
		return (err_msg(INVRGB, FALSE));
	return (TRUE);
}
