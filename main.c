/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:08:02 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 16:08:04 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_session	session;

	if (argc != 2)
		terminate_with_error(NULL, "Invalid input");
	validate_filename(argv[1]);
	ft_bzero(&session, sizeof(t_session));
	parse_map(&session, argv[1]);
	validate_map(&session);
	init_graphics(&session);
	load_textures(&session);
	render_map(&session);
	mlx_hook(session.display.window, ON_CLOSE, ON_CLOSE_MASK,
		close_game, &session);
	mlx_hook(session.display.window, ON_KEYPRESS, ON_KEYPRESS_MASK,
		handle_keypress, &session);
	mlx_loop_hook(session.display.mlx, update_frame, &session);
	mlx_loop(session.display.mlx);
}
