/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:07:14 by fsalazar          #+#    #+#             */
/*   Updated: 2023/09/19 19:21:27 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
// Libraries
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../mlx/lib/mlx_mac/mlx.h"
# include "Mac_Keys.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// Window Size (640 x 480)
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
// Texture Size (64 x 64)
# define TEX_SIZE 64
// BOOL
# define TRUE 1
# define FALSE 0
// Map
# define SPEED 0.125
# define ROT_SPEED 0.125
// Error Messages
# define USAGE "Usage: ./cub3d <map_of_your_choice.cub>\n"
# define NOTCUB "Error: File is not a .cub file\n"
# define NOTXMP "Error: File is not a .xpm file\n"
# define ISDIR "Error: File is a directory\n"
# define NOFILE "Error: File does not exist or missing permissions\n"
# define NOARG "Error: No file given\n"
# define INVRGB "Error: Invalid RGB value\n"
# define INVMAP "Error: Invalid map\n"
# define INVMAPCHAR "Error: Invalid map character\n"
# define INVNUMPLAYER "Error: Invalid number of players\n"
# define INVTEXTURE "Error: Invalid texture\n"
# define MISSINGTEXTURE "Error: Missing texture\n"
# define MISSINGRGB "Error: Missing RGB value\n"
# define INVPLAYERPOS "Error: Invalid player position\n"
# define MAPTOOSMALL "Error: Map is too small\n"
# define MAPMISSINGWALLS "Error: Map is missing walls\n"
# define MAPORDER "Error: Map is not last\n"
# define MALLOCFAIL "Error: Malloc failed\n"
# define MLXFAIL "Error: MLX failed\n"
# define MLXWINFAIL "Error: MLX window failed\n"
# define MLXIMGFAIL "Error: MLX image failed\n"

enum				e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			wall_dist;
	double			wall_x;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_map
{
	int				fd;
	int				line_count;
	int				width;
	int				height;
	int				eom;
	char			*path;
	char			**map;
}					t_map;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	int				texture_count;
	int				rgb_count;
	t_rgb			floor;
	t_rgb			ceiling;
	int				x;
	int				y;
	int				size;
	int				index;
	double			pos;
	double			step;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}					t_texture;

typedef struct s_player
{
	int				dir;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	int				has_moved;
	int				move_x;
	int				move_y;
	int				rotate;
	int				player_count;
}					t_player;

typedef struct s_img
{
	void			*img;
	int				*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_game
{
	int				win_width;
	int				win_height;
	void			*mlx;
	void			*win;
	int				**texture_pixels;
	int				**textures;
	char			**f_map;
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_texture		texture;
	t_img			img;
}					t_game;

// main.c
int					end_game(t_game *game);
int					final_count(t_game *game);
int					parse_args(t_game *game, char **argv);
// utils/free.c
void				free_texture_struct(t_texture *texture);
void				free_img_struct(t_img *img);
void				free_map_struct(t_map *map);
void				free_structs(t_game *game);
void				free_exit(t_game *game, int exit_code);
// utils/utils.c
int					array_size(char **array);
int					err_msg(char *msg, int ret);
int					ft_strcmp(char *s1, char *s2);
// utils/utils2.c
void				free_void_array(void **array);
void				free_int_array(int *array);
void				free_char_array(char **array);
char				*rem_nl(char *line);
// init/init_game.c
void				init_game(t_game *game);
void				init_rgb(t_rgb *rgb);
void				init_img(t_img *img);
void				init_map(t_map *map);
void				init_ray(t_ray *ray);
// init/init_player.c
void				init_player_north_south(t_player *player);
void				init_player_east_west(t_player *player);
void				init_player_pos(t_game *game);
void				init_player(t_player *player);
// init/init_mlx.c
void				init_mlx(t_game *game);
// init/textures.c
void				init_texture(t_texture *texture);
void				init_texture_img(t_game *game, t_img *image, char *path);
void				init_textures(t_game *game);
int					*xpm_to_img(t_game *game, char *path);
// parse/check_utils.c
int					ext_check_cub(char *file);
int					ext_check_xpm(char *file);
int					is_valid_file(char *file);
int					check_arg(char **argv);
int					comma_count(t_game *game);
// parse/f_map_finalize.c
void				resize_line(t_game *game, int i);
void				make_map_square(t_game *game);
void				fill_spaces_set_dimensions(t_game *game);
// parse/load_full_map.c
int					get_line_count(char *path);
int					load_info(t_game *game, char *path);
void				fill_map(t_game *game, int row, int col, int i);
// parse/map_wall_checks.c
int					check_top_bottom(t_game *game);
int					check_sides(t_game *game);
int					check_offsets(t_game *game);
int					check_map_walls(t_game *game);
// parse/parse_f_map.c
int					validate_final_map(t_game *game);
void				find_finalmap_dimensions(t_game *game);
int					check_validate_map(t_game *game);
int					check_validate_map_order(t_game *game);
// parse/parse_f_map2.c
int					check_map_chars(t_game *game);
int					check_player(t_game *game);
int					check_player_position(t_game *game);
int					check_empty_lines(t_game *game);
// parse/parse_rgb.c
unsigned long		rgb_to_hex(t_game *game, char *type);
int					load_rgb(t_game *game, char **rgb, char *type);
int					valid_rgb(t_game *game, char *line);
int					get_rgb(t_game *game, char *line);
int					check_validate_rgb(t_game *game);
// parse/parse_textures.c
int					valid_texture(char *line);
int					already_filled(char *line, t_game *game);
int					check_validate_textures(t_game *game);
char				*get_text(char *line, t_game *game);
// raycast/draw_frame.c
void				set_image_pixel(t_img *image, int x, int y, int color);
void				set_frame_image_pixel(t_game *game, t_img *image, int x,
						int y);
void				init_img_new(t_game *game, t_img *image, int width,
						int height);
void				draw_frame(t_game *game);
// raycast/init_text_pixels.c
void				init_texture_pixels(t_game *game);
// raycast/raycast_utils.c
void				init_raycast(t_game *game, t_ray *ray, int x);
void				set_dda(t_game *game, t_ray *ray);
void				perform_dda(t_game *game, t_ray *ray);
void				get_line_height(t_game *game, t_ray *ray);
void				update_texture_pixels(t_game *game, t_ray *ray, int x);
// raycast/raycast_utils2.c
void				get_texture_index(t_game *game, t_ray *ray);
// raycast/raycast.c
void				raycast(t_game *game);
// raycast/render_frame.c
void				render_frame(t_game *game);
int					render(t_game *game);
// movement/key_input.c
int					key_press_handler(int key, t_game *game);
int					key_release_handler(int key, t_game *game);
void				key_input(t_game *game);
// movement/move_player.c
int					move_player(t_game *game);
// movement/check_valid_move.c
bool				is_valid_pos(t_game *game, double x, double y);
int					check_movement(t_game *game, double new_x, double new_y);
// movement/rotate_player.c
int					rotate_left_right(t_game *game, double rotspeed);
int					rotate_player(t_game *game, double rot_dir);
// misc/debug_utils.c
void				print_map(t_game *game);
void				print_rgb(t_game *game);
void				print_final_map(t_game *game);
void				print_textures(t_game *game);
void				print_player(t_game *game);

#endif