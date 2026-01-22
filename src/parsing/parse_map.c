/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:16 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/21 20:14:08 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW", line[1]))
			return (0);
		i++;
	}
	return (1);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	parse_map_line(t_data *data, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (is_player(line[i]))
		{
			set_player(data, line[i], data->map.height, i);
			replace_player_by_zero(&data->map);
		}
		i++;
	}
	data->map.grid = add_line(data->map.grid, line);
	data->map.height++;
	len = ft_strlen(line);
	if (len > data->map.width)
		data->map.width = len;
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**add_line(char **grid, char *line)
{
	int		i;
	char	**new;
	int		len;

	len = 0;
	if (grid)
	{
		while (grid[len])
			len++;
	}
	i = 0;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (0);
	while (i < len)
	{
		new[i] = grid[i];
		i++;
	}
	new[i] = ft_strdup(line);
	if (!new)
		return (0);
	new[i + 1] = NULL;
	free(grid);
	return (new);
}
