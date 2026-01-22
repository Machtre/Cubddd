/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:44:23 by nguinot-          #+#    #+#             */
/*   Updated: 2026/01/14 11:18:06 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "structs.h"

// void	open_close_door(t_cub *cub)
// {
// 	int		x;
// 	int		y;
// 	char	tile;
	
// 	x = (int)(cub->player.x + cub->player.dir_x);
// 	y = (int)(cub->player.y + cub->player.dir_y);

// 	if (x < 0 || x >= cub->map.width || y < 0 || y >= cub->map.height)
// 		return;
// 	tile = cub->map.grid[y][x];
// 	if (tile == '2')
// 		cub->map.grid[y][x] = '0';
// 	else if (tile == '0')
// 		cub->map.grid[y][x] = '2';
// }

