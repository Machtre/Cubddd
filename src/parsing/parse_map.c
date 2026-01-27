/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:16 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/26 12:21:41 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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

void	parse_map_line(t_cub *cub, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (is_player(line[i]))
		{
			set_player(cub, line[i], cub->map.height, i);
			replace_player_by_zero(&cub->map);
		}
		i++;
	}
	cub->map.grid = add_line(cub->map.grid, line);
	cub->map.height++;
	len = ft_strlen(line);
	if (len > cub->map.width)
		cub->map.width = len;
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*new;

	if (!s)
		return (NULL);
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
		return (NULL);
	while (i < len)
	{
		new[i] = grid[i];
		i++;
	}
	new[i] = ft_strdup(line);
	if (!new[i])
	{
		free(new);
		return (NULL);
	}
	new[i + 1] = NULL;
	free(grid);
	return (new);
}

// 56 bytes in 1 blocks are still reachable in loss record 21 of 65
// ==81704==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==81704==    by 0x11161B: add_line (parse_map.c:96)
// ==81704==    by 0x1114C2: parse_map_line (parse_map.c:52)
// ==81704==    by 0x110D31: parse_line (parse.c:45)
// ==81704==    by 0x110DBB: parse_cub (parse.c:63)
// ==81704==    by 0x10FEE1: main (main.c:122)
// ==81704== 
// ==81704== 66 bytes in 6 blocks are still reachable in loss record 22 of 65
// ==81704==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==81704==    by 0x11029A: normalize_map (check_map.c:30)
// ==81704==    by 0x110E02: parse_cub (parse.c:68)
// ==81704==    by 0x10FEE1: main (main.c:122)