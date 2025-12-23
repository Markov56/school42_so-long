#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

# define BUFFER_SIZE	4096
# define VALID_TILES	"10PEC"
# define TILE_SIZE		64

typedef enum e_key
{
	W		= 119,
	A		= 97,
	S		= 115,
	D		= 100,
	UP		= 65362,
	DOWN	= 65364,
	LEFT	= 65361,
	RIGHT	= 65363,
	ESC		= 65307
}			t_key;

typedef enum e_tile
{
	WALL	= '1',
	SPACE	= '0',
	PLAYER	= 'P',
	EXIT	= 'E',
	COIN	= 'C',
}			t_tile;

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
} 			t_map;

typedef struct s_session
{
	t_map		map;
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

#endif