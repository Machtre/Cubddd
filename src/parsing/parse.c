/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:00 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/22 14:50:07 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_line(t_cub *cub, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		error(cub, "Malloc failed");
	if (!trimmed[0])
	{
		if (cub->parsing.in_map)
			cub->parsing.map_finished = 1;
		return (free(trimmed));
	}
	if (cub->parsing.map_finished)
		error(cub, "Invalid content after map");
	if (is_texture(trimmed))
	{
		if (cub->parsing.map_finished)
			error(cub, "Texture after map");
		parse_texture(cub, trimmed);
	}
	else if (is_color(trimmed))
	{
		if (cub->parsing.map_finished)
			error(cub, "Color after map");
		parse_color(cub, trimmed);
	}
	else if (is_map_line(trimmed))
	{
		cub->parsing.in_map = 1;
		parse_map_line(cub, trimmed);
	}
	else
		error(cub, "Invalid line in .cub file");
	free(trimmed);
}

void	parse_cub(t_cub *cub, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error(cub, "Cannot open file");
	init_data(cub);
	while ((line = get_next_line(fd)))
	{
		parse_line(cub, line);
		free(line);
	}
	close(fd);
	check_parsing_complete(cub);
	normalize_map(&cub->map);
	check_map(cub);
}

void	set_player(t_cub *cub, char dir, int y, int x)
{
	if (cub->player.start_dir)
		error(cub, "multiple player positions");
	cub->player.start_dir = dir;
	cub->player.x = x + 0.5;
	cub->player.y = y + 0.5;
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

void	check_parsing_complete(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cub->textures[i].path)
			error(cub, "Missing texture");
		i++;
	}
	if (cub->ceiling_color == -1 || cub->floor_color == -1)
		error(cub, "Missing floor or ceiling color");
	if (!cub->player.start_dir)
		error(cub, "Missing player");
	if (!cub->map.grid || cub->map.height == 0)
		error(cub, "Missing map");
}
