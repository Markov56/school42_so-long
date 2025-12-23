/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:11:02 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 16:11:04 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_graphics(t_session *session)
{
	int	window_width;
	int	window_height;

	session->display.mlx = mlx_init();
	if (!session->display.mlx)
		terminate_with_error(session, "Failed to initialize MLX");
	window_width = session->map->width * TILE_SIZE;
	window_height = session->map->height * TILE_SIZE;
	session->display.window = mlx_new_window(session->display.mlx,
			window_width, window_height, TITLE);
	if (!session->display.window)
		terminate_with_error(session, "Failed to create window");
}

void	load_textures(t_session *session)
{
	session->textures = malloc(TEXTURE_COUNT * sizeof(t_texture));
	if (!session->textures)
		terminate_with_error(session, "Failed to allocate texture memory");
	load_texture(session, &session->textures[TEX_WALL], WALL_IMG);
	load_texture(session, &session->textures[TEX_SPACE], SPACE_IMG);
	load_texture(session, &session->textures[TEX_PLAYER], PLAYER_IMG);
	load_texture(session, &session->textures[TEX_EXIT], EXIT_IMG);
	load_texture(session, &session->textures[TEX_COIN], COIN_IMG);
}

void	render_tile(t_session *session, t_position p)
{
	t_texture	texture;

	if (session->map->grid[p.y][p.x] == WALL)
		texture = session->textures[TEX_WALL];
	else if (session->map->grid[p.y][p.x] == SPACE)
		texture = session->textures[TEX_SPACE];
	else if (session->map->grid[p.y][p.x] == PLAYER)
		texture = session->textures[TEX_PLAYER];
	else if (session->map->grid[p.y][p.x] == COIN)
		texture = session->textures[TEX_COIN];
	else if (session->map->grid[p.y][p.x] == EXIT)
		texture = session->textures[TEX_EXIT];
	mlx_put_image_to_window(session->display.mlx, session->display.window, \
		texture.image, texture.width * p.x, texture.height * p.y);
}

void	render_map(t_session *session)
{
	int	x;
	int	y;

	y = 0;
	while (y < session->map->height)
	{
		x = 0;
		while (x < session->map->width)
		{
			render_tile(session, (t_position){x, y});
			x++;
		}
		y++;
	}
}

int	update_frame(t_session *session)
{
	char	next_tile;

	if (!is_valid_move(session))
		return (0);
	next_tile = session->map->grid
	[session->target_pos.y]
	[session->target_pos.x];
	if (next_tile == EXIT && session->collected == session->map->collectibles)
	{
		update_player_position(session);
		ft_putstr_fd("You won! Total moves: ", 1);
		ft_putnbr_fd(session->move_count, 1);
		ft_putstr_fd("\n", 1);
		close_game(session);
	}
	update_player_position(session);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(session->move_count, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
