/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:03:21 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/21 12:39:50 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	parse_args(t_game *game, char **argv)
{
	load_info(game, argv[1]);
	if (check_validate_textures(game) == FALSE)
		return (FALSE);
	if (check_validate_rgb(game) == FALSE)
		return (FALSE);
	if (check_validate_map_order(game) == FALSE)
		return (FALSE);
	if (check_validate_map(game) == FALSE)
		return (FALSE);
	fill_spaces_set_dimensions(game);
	make_map_square(game);
	return (TRUE);
}

int	end_game(t_game *game)
{
	free_exit(game, 0);
	return (0);
}

int	final_count(t_game *game)
{
	int	final_count;
	int	total_count;
	int	i;

	final_count = (game->texture.texture_count + game->texture.rgb_count
			+ game->map.height);
	total_count = 0;
	i = 0;
	while (game->map.map[i])
	{
		if (game->map.map[i][0] != '\n' && game->map.map[i][0] != '\0')
			total_count++;
		i++;
	}
	if (final_count != total_count)
	{
		printf("Error: Invalid Characted\n");
		return (FALSE);
	}
	return (TRUE);
}
// while true; do leaks cub3D; sleep 1; clear; done
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (err_msg(USAGE, 1));
	if (check_arg(argv) == FALSE)
		return (1);
	init_game(&game);
	if (parse_args(&game, argv) == FALSE)
		free_exit(&game, 1);
	if (final_count(&game) == FALSE)
		free_exit(&game, 1);
	init_player_pos(&game);
	init_mlx(&game);
	init_textures(&game);
	render_frame(&game);
	key_input(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	free_exit(&game, 0);
}
