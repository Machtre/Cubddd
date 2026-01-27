/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:56:24 by nguinot-          #+#    #+#             */
/*   Updated: 2026/01/26 11:04:43 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "../minilibx/minilibx-linux/mlx.h"

static void	load_texture(t_cub *cub, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Erreur: impossible de charger %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
}
t_tex *get_wall_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return(&cub->wall_west);
		else
			return (&cub->wall_east);
	}
	else
	{
		if (ray->step_y > 0)
			return (&cub->wall_north);
		else
			return(&cub->wall_south);
	}
}

void	load_textures(t_cub *cub)
{
	load_texture(cub, &cub->wall_north, "./north.xpm");
	load_texture(cub, &cub->wall_south, "./south.xpm");
	load_texture(cub, &cub->wall_east, "./east.xpm");
	load_texture(cub, &cub->wall_west, "./west.xpm");
}

