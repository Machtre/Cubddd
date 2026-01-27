#include "structs.h"
#include "structs.h"
#include "../minilibx/minilibx-linux/mlx.h"

// Map de test avec portes (2 = porte fermée)
// char *g_test_map[] = {
//     "111111111111",
//     "100000000001",
//     "101000000001",
//     "100000000001",
//     "100000100001",
//     "10000000S001",
//     "100000000001",
//     "111111111111",
//     NULL
// };

// void init_map(t_cub *cub)
// {
// 	int i;
// 	int max_width;

// 	i = 0;
// 	max_width = 0;
	
// 	// Compter la hauteur et trouver la largeur max
// 	while (g_test_map[i])
// 	{
// 		int len = 0;
// 		while (g_test_map[i][len])
// 			len++;
// 		if (len > max_width)
// 			max_width = len;
// 		i++;
// 	}
	
// 	cub->map.height = i;
// 	cub->map.width = max_width;
// 	cub->map.grid = g_test_map;
// }

void init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		printf("Erreur: mlx_init a échoué\n");
		exit(1);
	}
	
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "Cub3D - Test Raycasting");
	if (!cub->win)
	{
		printf("Erreur: mlx_new_window a échoué\n");
		exit(1);
	}
	
	cub->img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->img)
	{
		printf("Erreur: mlx_new_image a échoué\n");
		exit(1);
	}
	
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, &cub->line_len, &cub->endian);
}

void clear_image(t_cub *cub)
{
	int x, y;
	
	// Dessiner le plafond (gris clair)
	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			my_mlx_pixel_put(cub, x, y, cub->floor_color);
			x++;
		}
		y++;
	}
	
	// Dessiner le sol (gris foncé)
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			my_mlx_pixel_put(cub, x, y, cub->ceiling_color);
			x++;
		}
		y++;
	}
}

int render_frame(t_cub *cub)
{
	clear_image(cub);
	raycasting(cub);
	draw_minimap(cub);
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	return (0);
}

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	free_data(cub);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	// t_data data;
	t_cub cub;
	memset(&cub, 0, sizeof(t_cub));
	init_data(&cub);
	parse_cub(&cub, argv[1]);
	// memset(&cub, 0, sizeof(t_cub));
	cub.move_speed = 0.01;
	cub.move_speed = 0.01;
	// init_map(&cub);
	init_player(&cub);
	init_mlx(&cub);
	load_textures(&cub);
	render_frame(&cub);
	mlx_hook(cub.win, 2, 1L<<0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L<<1, key_release, &cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, update_player, &cub);
	mlx_loop(cub.mlx);
	
	return (0);
}


