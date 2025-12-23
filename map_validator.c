#include "so_long.h"

static int	is_rectangular(t_map *map)
{
	int	row;
	int	expected_width;

	if (map->height == 0)
		return (0);
	expected_width = ft_strlen(map->grid[0]);
	row = 0;
	while (row < map->height)
	{
		if (ft_strlen(map->grid[row]) != expected_width)
			return (0);
		row++;
	}
	map->width = expected_width;
	return (1);
}

static int	is_surrounded_by_walls(t_map *map)
{
	int	row;
	int	col;

	row = 0;

	while (row < map->height)
	{
		if (map->grid[row][0] != WALL || 
			map->grid[row][map->width - 1] != WALL)
			return (0);
		row++;
	}
	col = 0;
	while (col < map->width)
	{
		if (map->grid[0][col] != WALL || 
			map->grid[map->height - 1][col] != WALL)
			return (0);
		col++;
	}
	return (1);
}

static int	validate_tiles_and_count(t_map *map, t_session *session)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->grid[row][col] == PLAYER)
			{
				map->players++;
				session->current_pos = (t_position){col, row};
				session->target_pos = session->current_pos;
			}
			else if (map->grid[row][col] == EXIT)
				map->exits++;
			else if (map->grid[row][col] == COIN)
				map->collectibles++;
			else if (!ft_strchr(VALID_TILES, map->grid[row][col]))
				return (0);
			col++;
		}
		row++;
	}
	return (map->players == 1 && map->exits == 1 
		&& map->collectibles >= 1);
}

static int	verify_valid_path(t_map *map, t_session *session)
{
	char	**temp_grid;
	int		path_exists;
	int	row;

	temp_grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!temp_grid)
		terminate_with_error(session, "Memory allocation failed");
	row = 0;
	while (row < map->height)
	{
		temp_grid[row] = ft_strdup(map->grid[row]);
		if (!temp_grid[row])
		{
			free_grid(temp_grid);
			terminate_with_error(session, "Memory allocation failed");
		}
		row++;
	}
	path_exists = flood_fill_check(map, session->current_pos, temp_grid);
	free_grid(temp_grid);
	return (path_exists);
}

void	validate_map(t_session *session)
{
	if (session->map.height == 0)
		terminate_with_error(session, "Map is empty");
	if (!is_rectangular(&session->map))
		terminate_with_error(session, "Map must be rectangular");
	if (!is_surrounded_by_walls(&session->map))
		terminate_with_error(session, "Map must be surrounded by walls");
	if (!validate_tiles_and_count(&session->map, session))
		terminate_with_error(session, "Invalid map tiles or object count");
	if (!verify_valid_path(&session->map, session))
		terminate_with_error(session, "No valid path to exit");
}