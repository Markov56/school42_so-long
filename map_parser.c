/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarkov <rmarkov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:08:20 by rmarkov           #+#    #+#             */
/*   Updated: 2025/12/23 16:08:22 by rmarkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*read_entire_file(int fd)
{
	char	*result;
	char	*buffer;
	char	*temp;
	int		bytes;

	result = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!result || !buffer)
		return (free(result), free(buffer), NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		temp = ft_strjoin(result, buffer);
		free(result);
		if (!temp)
			return (free(buffer), NULL);
		result = temp;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes < 0)
		return (free(result), NULL);
	return (result);
}

static int	count_lines(char **lines)
{
	int	count;

	count = 0;
	while (lines[count])
		count++;
	return (count);
}

// TODO check with different files. mb get_next_line is needed
void	parse_map(t_session *session, char *file)
{
	int		fd;
	char	*content;
	char	**lines;

	session->map = malloc(sizeof(t_map));
	if (!session->map)
		terminate_with_error(session, "Memore allocation failed");
	ft_bzero(session->map, sizeof(t_map));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate_with_error(session, "Cannot open map file");
	content = read_entire_file(fd);
	close(fd);
	if (!content)
		terminate_with_error(session, "Failed to read file");
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		terminate_with_error(session, "Failed to parse map");
	session->map->grid = lines;
	session->map->height = count_lines(lines);
}
