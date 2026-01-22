/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:30:25 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/21 20:11:44 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_color(char *line)
{
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		return (1);
	return (0);
}

void	check_rgb(t_data *data, char **rgb)
{
	int	i;
	int	j;
	int	value;

	i = 0;
	value = 0;
	while (i < 3)
	{
		if (!rgb[i][0])
			error(data, "Empty RGB value");
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_is_digit(rgb[i][j]))
				error(data, "Value must be a digit");
			j++;
		}
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			error(data, "RGB value out of range");
		i++;
	}
}

void	parse_color(t_data *data, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (count_tab(split) != 2)
		error(data, "Invalid color format");
	rgb = ft_split(split[1], ',');
	if (count_tab(rgb) != 3)
		error(data, "Invalid RGB value");
	check_rgb(data, rgb);
	set_color(data, split[0][0], rgb);
	free_tab(rgb);
	free_tab(split);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	set_color(t_data *data, char id, char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error(data, "RGB out of range");
	if (id == 'F')
	{
		if (data->floor_color != -1)
			error(data, "Duplicate floor color");
		data->floor_color = rgb_to_int(r, g, b);
	}
	else if (id == 'C')
	{
		if (data->ceiling_color != -1)
			error(data, "Duplicate ceilling color");
		data->ceiling_color = rgb_to_int(r, g, b);
	}
}
