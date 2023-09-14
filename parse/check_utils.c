/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:20:38 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:09 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ext_check_cub(char *file)
{
	int	i;

	i = 0;
	if (!file || ft_strlen(file) < 5)
		return (err_msg(NOFILE, FALSE));
	while (file[i])
		i++;
	if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3]
		== 'c' && file[i - 4] == '.')
		return (TRUE);
	return (err_msg(NOTCUB, FALSE));
}

int	ext_check_xpm(char *file)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!file || ft_strlen(file) < 5)
		return (err_msg(NOFILE, FALSE));
	tmp = rem_nl(file);
	while (tmp[i])
		i++;
	if (!(tmp[i - 1] == 'm') && !(tmp[i - 2] == 'p') && !(tmp[i - 3] == 'x')
		&& !(tmp[i - 4] == '.'))
	{
		free(tmp);
		return (err_msg(NOTXMP, FALSE));
	}
	if (!is_valid_file(tmp))
	{
		free(tmp);
		return (err_msg(NOFILE, FALSE));
	}
	free(tmp);
	return (TRUE);
}

int	is_valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	if (access(file, R_OK) == -1)
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

int	check_arg(char **argv)
{
	if (!ext_check_cub(argv[1]))
		return (err_msg(NOTCUB, 1), FALSE);
	if (!is_valid_file(argv[1]))
		return (err_msg(NOFILE, 1), FALSE);
	return (TRUE);
}

int	comma_count(t_game *game)
{
	int	i;
	int	j;
	int	commas;

	i = 0;
	commas = 0;
	while (game->map.map[i])
	{
		j = 0;
		if (game->map.map[i][0] == 'F' || game->map.map[i][0] == 'C')
		{
			while (game->map.map[i][j])
			{
				if (game->map.map[i][j] == ',')
					commas++;
				j++;
			}
		}
		i++;
	}
	if (commas != 4)
		return (FALSE);
	return (TRUE);
}
