/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:39:46 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:42:52 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_raycast(t_game *game, t_ray *ray, int x)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	set_dda(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->player.pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->player.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->deltadist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.5 || ray->map_x < 0.5
			|| ray->map_y > game->map.height - 0.5
			|| ray->map_x > game->map.width - 0.5)
			break ;
		else if (game->f_map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

void	get_line_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(game->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	update_texture_pixels(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(game, ray);
	game->texture.x = (int)(ray->wall_x * game->texture.size);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		game->texture.x = game->texture.size - game->texture.x - 1;
	game->texture.step = 1.0 * game->texture.size / ray->line_height;
	game->texture.pos = (ray->draw_start - game->win_height / 2
			+ ray->line_height / 2) * game->texture.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		game->texture.y = (int)game->texture.pos & (game->texture.size - 1);
		game->texture.pos += game->texture.step;
		color = game->textures[game->texture.index][game->texture.size
			* game->texture.y + game->texture.x];
		if (game->texture.index == NORTH || game->texture.index == WEST)
			color = (color >> 1) & 8355700;
		if (color > 0)
			game->texture_pixels[y][x] = color;
		y++;
	}
}
