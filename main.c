#include "so_long.h"

void	start_session(char *map_file)
{
	t_session	session;

	ft_bzero(&session, sizeof(t_session));
	parse_map(&session, map_file);
	validate_map(&session);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		terminate_with_error(NULL, "Invalid input");
	validate_filename(argv[1]);
	start_session(argv[1]);
}