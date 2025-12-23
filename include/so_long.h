/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:07:46 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 16:07:48 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define BUFFER_SIZE	4096
# define TEXTURE_COUNT	5
# define TILE_SIZE		32
# define VALID_TILES	"10PEC"
# define TITLE			"so_long"
# define WALL_IMG		"assets/img/wall.xpm"
# define SPACE_IMG		"assets/img/space.xpm"
# define PLAYER_IMG		"assets/img/player.xpm"
# define EXIT_IMG		"assets/img/exit.xpm"
# define COIN_IMG		"assets/img/coin.xpm"

typedef enum e_key
{
	KEY_W		= 119,
	KEY_A		= 97,
	KEY_S		= 115,
	KEY_D		= 100,
	UP			= 65362,
	DOWN		= 65364,
	LEFT		= 65361,
	RIGHT		= 65363,
	ESC			= 65307
}			t_key;

typedef enum e_tile
{
	WALL	= '1',
	SPACE	= '0',
	PLAYER	= 'P',
	EXIT	= 'E',
	COIN	= 'C',
}			t_tile;

typedef enum e_texture_id
{
	TEX_WALL,
	TEX_SPACE,
	TEX_PLAYER,
	TEX_EXIT,
	TEX_COIN,
}			t_texture_id;

typedef enum e_event
{
	ON_KEYPRESS			= 2,
	ON_CLOSE	= 17,
}				t_event;

typedef enum e_mask
{
	ON_KEYPRESS_MASK			= (1L << 0),
	ON_CLOSE_MASK		= (1L << 17)
}					t_mask;

typedef struct s_position
{
	int	x;
	int	y;
}			t_position;

typedef struct s_display
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*buffer;
}			t_display;

typedef struct s_texture
{
	void	*image;
	int		height;
	int		width;
}			t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
}			t_map;

typedef struct s_session
{
	t_map		*map;
	t_position	current_pos;
	t_position	target_pos;
	t_display	display;
	t_texture	*textures;
	int			collected;
	int			move_count;
}				t_session;

void	validate_filename(char *file);
int		terminate_with_error(t_session *session, char *message);
void	parse_map(t_session *session, char *file);
void	validate_map(t_session *session);
void	free_grid(char **grid);
int		flood_fill_check(t_map *map, t_position pos, char **temp_grid);
void	process_tile(t_map *map, t_session *session, int row, int col);
void	init_graphics(t_session *session);
void	load_textures(t_session *session);
void	render_map(t_session *session);
int		close_game(t_session *session);
int		is_valid_move(t_session *session);
void	update_player_position(t_session *session);
int		handle_keypress(int keycode, t_session *session);
int		update_frame(t_session *session);
void	load_texture(t_session *session, t_texture *tex, char *path);
void	cleanup_session(t_session *session);
void	render_tile(t_session *session, t_position p);

#endif
