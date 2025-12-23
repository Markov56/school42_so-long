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

int	terminate_with_error(t_session *session, char *message)
{
	//TODO clean before exit
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

// TODO might be problems with static variables
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