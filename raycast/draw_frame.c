/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:36:00 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:38:28 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_len / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	if (game->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, game->texture_pixels[y][x]);
	else if (y < game->win_height / 2)
		set_image_pixel(image, x, y, game->texture.hex_ceiling);
	else if (y < game->win_height -1)
		set_image_pixel(image, x, y, game->texture.hex_floor);
}

void	init_img_new(t_game *game, t_img *image, int width, int height)
{
	init_img(image);
	image->img = mlx_new_image(game->mlx, width, height);
	if (image->img == NULL)
		free_exit(game, 1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return ;
}

void	draw_frame(t_game *game)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img_new(game, &image, game->win_width, game->win_height);
	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			set_frame_image_pixel(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}
