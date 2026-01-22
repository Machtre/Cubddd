/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:23 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/21 20:14:53 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	normalize_map(t_map *map)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (i < map->height)
	{
		new = malloc(map->width + 1);
		if (!new)
			return ;
		j = 0;
		while (j < map->width)
		{
			if (j < (int)ft_strlen(map->grid[i]))
				new[j] = map->grid[i][j];
			else
				new[j] = ' ';
			j++;
		}
		new[j] = '\0';
		free(map->grid[i]);
		map->grid[i] = new;
		i++;
	}
}

int	is_walkable(char c)
{
	if (c == '0' || is_player(c))
		return (1);
	return (0);
}

void	check_map_closed(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (is_walkable(data->map.grid[y][x]))
			{
				if (y == 0 || x == 0 || y == data->map.height - 1
					|| x == data->map.width - 1)
					error(data, "Map not closed (open border)");
				if (data->map.grid[y][x - 1] == ' ' || data->map.grid[y][x
					+ 1] == ' ' || data->map.grid[y - 1][x] == ' '
					|| data->map.grid[y + 1][x] == ' ')
					error(data, "Map not closed (hole)");
			}
			x++;
		}
		y++;
	}
}

void	check_map_char(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (!ft_strchr("01 NSEW", data->map.grid[y][x]))
				error(data, "Invalid chararcter in map");
			x++;
		}
		y++;
	}
}

void	check_map(t_data *data)
{
	check_map_char(data);
	check_map_closed(data);
}
