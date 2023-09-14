/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:44 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/14 12:11:14 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture_struct(t_texture *texture)
{
	if (texture->north != NULL)
		free(texture->north);
	if (texture->south != NULL)
		free(texture->south);
	if (texture->west != NULL)
		free(texture->west);
	if (texture->east != NULL)
		free(texture->east);
}

void	free_img_struct(t_img *img)
{
	if (img->img != NULL)
		free(img->img);
	if (img->addr != NULL)
		free(img->addr);
}

void	free_map_struct(t_map *map)
{
	if (map->map != NULL)
		free_char_array(map->map);
	if (map->path != NULL)
		free(map->path);
}

void	free_structs(t_game *game)
{
	if (game->textures)
		free_void_array((void **)game->textures);
	if (game->texture_pixels)
		free_void_array((void **)game->texture_pixels);
	if (game->f_map)
		free_char_array(game->f_map);
	free_map_struct(&game->map);
	free_texture_struct(&game->texture);
	free_img_struct(&game->img);
}

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }
// leaks();
void	free_exit(t_game *game, int exit_code)
{
	if (!game)
		exit(exit_code);
	free_structs(game);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	exit(exit_code);
}
