/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguinot- <nguinot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:14:50 by nguinot-          #+#    #+#             */
/*   Updated: 2026/01/13 16:32:51 by nguinot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	rotate_player(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x; //save ancienne direction x
	cub->player.dir_x = cub->player.dir_x * cos(rot_speed) - cub->player.dir_y
		 * sin(rot_speed); //rotation dir x
	cub->player.dir_y = old_dir_x * sin(rot_speed) + cub->player.dir_y
		 * cos(rot_speed); // rotation dir y
	old_plane_x = cub->player.plane_x; // save ancien plane x
	cub->player.plane_x = cub->player.plane_x * cos(rot_speed) //rotation plan FOV
		 - cub->player.plane_y * sin(rot_speed);
	cub->player.plane_y = old_plane_x * sin(rot_speed) + cub->player.plane_y
		 * cos(rot_speed);
}
