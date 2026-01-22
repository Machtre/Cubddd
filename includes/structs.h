#ifndef STRUCTS_H
# define STRUCTS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



# define WIN_W 800
# define WIN_H 600

typedef struct s_player
{
	double x; // pos sur l'axe X
	double y; // pos sur l'axe Y
	double dir_x; // vecteur dir regard (x)
	double dir_y; // vecteur dir regard Y
	double plane_x; // vecteur camera x
	double plane_y; // vecteur camera y
	char	start_dir;
}	t_player;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
}	t_map;

typedef struct s_ray
{
	double	camera_x; // pos x sur plan camera entre -1 et 1
	double	ray_dir_x; // dir rayon
	double	ray_dir_y;

	int		map_x; //case de depart
	int		map_y;

	double	side_dist_x; //distances a parcourir avant prochaine frontiere  
	double	side_dist_y;

	double	delta_dist_x; //cout pr traverser case
	double	delta_dist_y;

	double	perp_wall_dist; // distance perpendicullaire entre joueur et mur touche

	int		step_x; // sens de deplacement, -1 / +1
	int		step_y;
	int		hit; //indicateur 0/1 mur touche ou pas
	int		side; // indicateur type de mur touche (vertical(x) / horizontal(y))
}	t_ray;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_cub
{
	t_player	player; // donees
	t_map	map;
	t_ray	ray;

	void	*mlx; //contexte mlx
	void	*win;
	
	void	*img; //images de rendu
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	move_speed;

	t_tex	wall_north;
	t_tex	wall_south;
	t_tex	wall_east;
	t_tex	wall_west;

	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_left;
	int	key_right;
	int	key_e;
} t_cub;

typedef struct s_draw_data
{
	t_tex	*tex;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_draw_data;

//RENDERING
//raycasting.c
void	raycasting(t_cub *cub);
//utils_raycasting.c
void	init_ray(t_cub *cub, t_ray *ray, int x);
void	calc_step_and_side_dist(t_cub *cub, t_ray *ray);
void	perform_dda(t_cub *cub, t_ray *ray);
void	calc_wall_distance(t_ray *ray);
void	init_var(t_cub *cub, t_ray *ray, int x);
void	draw_wall_column(t_cub *cub, int x, int y, int draw_end, char tile);
void	draw_wall(t_cub *cub, t_ray *ray, int x);
void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

//MOVEMENT
//rot.c
void	rotate_player(t_cub *cub, double rot_speed);
//move_player.c
void	move_forward(t_cub *cub);
void	move_backward(t_cub *cub);
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);
//key_hook.c
int	key_press(int keycode, t_cub *cub);
int	key_release(int keycode, t_cub *cub);
int update_player(t_cub *cub);
//main.c
int	render_frame(t_cub *cub);
int	close_window(t_cub *cub);
//door.c
void	open_close_door(t_cub *cub);
//spawn.c
void	init_player(t_cub *cub);
void	set_direction(t_cub *cub, char d);

//TEXTURES
//init_textures.c
void	load_textures(t_cub* cub);
t_tex *get_wall_texture(t_cub *cub, t_ray *ray);


#endif