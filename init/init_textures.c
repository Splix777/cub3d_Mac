/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:10:54 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:13:09 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_texture(t_texture *texture)
{
	texture->north = NULL;
	texture->south = NULL;
	texture->east = NULL;
	texture->west = NULL;
	init_rgb(&texture->floor);
	init_rgb(&texture->ceiling);
	texture->x = 0;
	texture->y = 0;
	texture->size = TEX_SIZE;
	texture->index = 0;
	texture->pos = 0;
	texture->step = 0;
	texture->hex_floor = 0x0;
	texture->hex_ceiling = 0x0;
}

void	init_texture_img(t_game *game, t_img *image, char *path)
{
	init_img(image);
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture.size,
			&game->texture.size);
	if (image->img == NULL)
		free_exit(game, 1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return ;
}

int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * game->texture.size
			* game->texture.size);
	if (!buffer)
		free_exit(game, 1);
	y = 0;
	while (y < game->texture.size)
	{
		x = 0;
		while (x < game->texture.size)
		{
			buffer[y * game->texture.size + x] = tmp.addr[y * game->texture.size
				+ x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_game *game)
{
	game->textures = ft_calloc(5, sizeof * game->textures);
	if (!game->textures)
	{
		err_msg(MALLOCFAIL, 1);
		free_exit(game, 1);
	}
	game->textures[NORTH] = xpm_to_img(game, game->texture.north);
	game->textures[SOUTH] = xpm_to_img(game, game->texture.south);
	game->textures[EAST] = xpm_to_img(game, game->texture.east);
	game->textures[WEST] = xpm_to_img(game, game->texture.west);
}
