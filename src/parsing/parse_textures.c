/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:09 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/20 18:26:12 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_texture(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

void	set_texture(t_data *data, char *id, char *path)
{
	int	index;

	index = 0;
	if (!ft_strcmp(id, "NO"))
		index = NO;
	else if (!ft_strcmp(id, "SO"))
		index = SO;
	else if (!ft_strcmp(id, "EA"))
		index = EA;
	else if (!ft_strcmp(id, "WE"))
		index = WE;
	else
		error(data, "Unknown texture identifier");
	if (data->textures[index].path)
		error(data, "Duplicate texture");
	data->textures[index].path = ft_strdup(path);
}

void	parse_texture(t_data *data, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (count_tab(split) != 2)
		error(data, "Invalid texture line");
	set_texture(data, split[0], split[1]);
	free_tab(split);
}
