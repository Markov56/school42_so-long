/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:08:10 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 16:08:12 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_filename(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (i < 5)
		terminate_with_error(NULL, "Invalid filename");
	if (!ft_strnstr((file + i - 4), ".ber", 4))
		terminate_with_error(NULL, "Invalid file extension");
}

int	terminate_with_error(t_session *session, char *message)
{
	cleanup_session(session);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	flood_fill_check(t_map *map, t_position pos, char **temp_grid)
{
	static int	coins_found = 0;
	static int	exit_found = 0;

	if (pos.y >= map->height || pos.x >= map->width)
		return (0);
	if (temp_grid[pos.y][pos.x] == WALL || 
		temp_grid[pos.y][pos.x] == 'V')
		return (0);
	if (temp_grid[pos.y][pos.x] == COIN)
		coins_found++;
	if (temp_grid[pos.y][pos.x] == EXIT)
		exit_found = 1;
	temp_grid[pos.y][pos.x] = 'V';
	flood_fill_check(map, (t_position){pos.x, pos.y + 1}, temp_grid);
	flood_fill_check(map, (t_position){pos.x, pos.y - 1}, temp_grid);
	flood_fill_check(map, (t_position){pos.x + 1, pos.y}, temp_grid);
	flood_fill_check(map, (t_position){pos.x - 1, pos.y}, temp_grid);
	return (coins_found == map->collectibles && exit_found);
}

void	load_texture(t_session *session, t_texture *tex, char *path)
{
	tex->image = mlx_xpm_file_to_image(session->display.mlx,
			path, &tex->width, &tex->height);
	if (!tex->image)
		terminate_with_error(session, "Failed to load texture");
}

void	process_tile(t_map *map, t_session *session, int row, int col)
{
	char	tile;

	tile = map->grid[row][col];
	if (tile == PLAYER)
	{
		map->players++;
		session->current_pos = (t_position){col, row};
		session->target_pos = session->current_pos;
	}
	else if (tile == EXIT)
		map->exits++;
	else if (tile == COIN)
		map->collectibles++;
}
