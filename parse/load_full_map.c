/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_full_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:22:21 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/13 16:22:52 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_line_count(char *path)
{
	int		fd;
	int		line_count;
	char	*line;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg(NOFILE, 0));
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

void	fill_map(t_game *game, int row, int col, int i)
{
	char	*line;

	line = get_next_line(game->map.fd);
	while (line != NULL)
	{
		game->map.map[row] = malloc(sizeof(char) * ft_strlen(line) + 1);
		if (!game->map.map[row])
		{
			err_msg(MALLOCFAIL, 0);
			free(line);
			game->map.map[row] = NULL;
			return ;
		}
		col = 0;
		while (line[i])
			game->map.map[row][col++] = line[i++];
		game->map.map[row][col] = '\0';
		row++;
		i = 0;
		free(line);
		line = get_next_line(game->map.fd);
	}
	game->map.map[row] = NULL;
}

int	load_info(t_game *game, char *path)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	row = 0;
	col = 0;
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd < 0)
		return (err_msg(NOFILE, 0));
	game->map.path = ft_strdup(path);
	game->map.line_count = get_line_count(path);
	if (game->map.line_count <= 10)
		return (err_msg(INVMAP, 0));
	game->map.map = ft_calloc(game->map.line_count + 1, sizeof(char *));
	if (!game->map.map)
		return (err_msg(MALLOCFAIL, 0));
	fill_map(game, row, col, i);
	close(game->map.fd);
	return (TRUE);
}
