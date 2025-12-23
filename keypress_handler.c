/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:04:29 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 22:04:30 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_move(t_session *session)
{
	if (session->current_pos.x == session->target_pos.x && 
		session->current_pos.y == session->target_pos.y)
		return (0);
	if (session->map->grid[session->target_pos.y]
		[session->target_pos.x] == WALL)
		return (0);
	return (1);
}

void	update_player_position(t_session *session)
{
	static char	previous_tile = SPACE;
	char		next_tile;

	session->map->grid
	[session->current_pos.y][session->current_pos.x] = previous_tile;
	next_tile = session->map->grid
	[session->target_pos.y][session->target_pos.x];
	if (next_tile == COIN)
	{
		session->collected++;
		previous_tile = SPACE;
	}
	else
		previous_tile = next_tile;
	session->map->grid[session->target_pos.y][session->target_pos.x] = PLAYER;
	render_tile(session, session->current_pos);
	render_tile(session, session->target_pos);
	session->current_pos = session->target_pos;
	session->move_count++;
}

int	handle_keypress(int keycode, t_session *session)
{
	if (keycode == ESC)
		close_game(session);
	else if (keycode == KEY_W || keycode == UP)
		session->target_pos = (t_position){session->current_pos.x, 
			session->current_pos.y - 1};
	else if (keycode == KEY_S || keycode == DOWN)
		session->target_pos = (t_position){session->current_pos.x, 
			session->current_pos.y + 1};
	else if (keycode == KEY_A || keycode == LEFT)
		session->target_pos = (t_position){session->current_pos.x - 1, 
			session->current_pos.y};
	else if (keycode == KEY_D || keycode == RIGHT)
		session->target_pos = (t_position){session->current_pos.x + 1, 
			session->current_pos.y};
	return (0);
}
