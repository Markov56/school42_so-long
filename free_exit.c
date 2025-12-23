/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:04:19 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 22:04:21 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free_grid(map->grid);
	free(map);
}

void	free_textures(t_session *session)
{
	int	i;

	if (!session->textures)
		return ;
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (session->textures[i].image)
			mlx_destroy_image(session->display.mlx, 
				session->textures[i].image);
		i++;
	}
	free(session->textures);
}

void	cleanup_session(t_session *session)
{
	if (!session)
		return ;
	if (session->map)
		free_map(session->map);
	if (session->textures)
		free_textures(session);
	if (session->display.window)
		mlx_destroy_window(session->display.mlx, session->display.window);
	if (session->display.mlx)
	{
		mlx_destroy_display(session->display.mlx);
		free(session->display.mlx);
	}
}

int	close_game(t_session *session)
{
	cleanup_session(session);
	exit(0);
}
