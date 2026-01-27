/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:32:20 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/27 18:39:41 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = cub->addr + (y * cub->line_len + x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}


void	draw_circle(t_cub *cub, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(cub, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub *cub)
{
	int	px;
	int	py;

	px = MM_X + cub->player.x * MM_SCALE;
	py = MM_Y + cub->player.y * MM_SCALE;
	
	draw_circle(cub, px, py, 3, 0xFF0000);
}

void	draw_line(t_cub *cub, int x0, int y0, int x1, int y1, int color)
{
	int	steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	int	i;

	int dx = x1 - x0;
	int dy = y1 - y0;

	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	x_inc = dx / (double)steps;
	y_inc = dy / (double)steps;

	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		put_pixel(cub, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}


void	draw_minimap(t_cub *cub)
{
	int y;
	int x;

	y = 0;
	while (cub->map.grid[y])
	{
		x = 0;
		while (cub->map.grid[y][x])
		{
			if (cub->map.grid[y][x] == '1')
				draw_square(cub, MM_X + x * MM_SCALE, MM_Y + y * MM_SCALE,
					MM_SCALE, 0x444444);
			else
				draw_square(cub, MM_X + x * MM_SCALE, MM_Y + y * MM_SCALE,
				MM_SCALE, 0xCCCCCC);
			x++;
		}
		y++;
	}
}