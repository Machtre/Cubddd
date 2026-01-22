/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:00 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/21 20:12:44 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse_line(t_data *data, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		error(data, "Malloc failed");
	if (!trimmed[0])
	{
		if (data->parsing.in_map)
			data->parsing.map_finished = 1;
		return (free(trimmed));
	}
	if (data->parsing.map_finished)
		error(data, "Invalid content after map");
	if (is_texture(trimmed))
	{
		if (data->parsing.map_finished)
			error(data, "Texture after map");
		parse_texture(data, trimmed);
	}
	else if (is_color(trimmed))
	{
		if (data->parsing.map_finished)
			error(data, "Color after map");
		parse_color(data, trimmed);
	}
	else if (is_map_line(trimmed))
	{
		data->parsing.in_map = 1;
		parse_map_line(data, trimmed);
	}
	else
		error(data, "Invalid line in .cub file");
	free(trimmed);
}

void	parse_cub(t_data *data, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error(data, "Cannot open file");
	init_data(data);
	while ((line = get_next_line(fd)))
	{
		parse_line(data, line);
		free(line);
	}
	close(fd);
	check_parsing_complete(data);
	normalize_map(&data->map);
	check_map(data);
}

void	set_player(t_data *data, char dir, int y, int x)
{
	if (data->player.start_dir)
		error(data, "multiple player positions");
	data->player.start_dir = dir;
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
}

void	replace_player_by_zero(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player(map->grid[y][x]))
				map->grid[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	check_parsing_complete(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!data->textures[i].path)
			error(data, "Missing texture");
		i++;
	}
	if (data->ceiling_color == -1 || data->floor_color == -1)
		error(data, "Missing floor or ceiling color");
	if (!data->player.start_dir)
		error(data, "Missing player");
	if (!data->map.grid || data->map.height == 0)
		error(data, "Missing map");
}
