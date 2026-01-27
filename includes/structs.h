#ifndef STRUCTS_H
# define STRUCTS_H

# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MM_SCALE 8 // taille d’une case en pixels
# define MM_X 20    // position mini-map écran
# define MM_Y 20

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define WIN_W 800
# define WIN_H 600

typedef struct s_parsing
{
	int			in_map;
	int			map_finished;
}				t_parsing;

typedef struct s_texture
{
	char *path; // Chemin vers le .xpm
	void *img;  // Image MLX
	int			width;
	int			height;
	int *addr; // Pixels
}				t_texture;

typedef struct s_player
{
	double x;       // pos sur l'axe X
	double y;       // pos sur l'axe Y
	double dir_x;   // vecteur dir regard (x)
	double dir_y;   // vecteur dir regard Y
	double plane_x; // vecteur camera x
	double plane_y; // vecteur camera y
	char		start_dir;
}				t_player;

enum			e_tex
{
	NO,
	SO,
	WE,
	EA
};

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_data
{
	t_map		map;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	t_player	player;
	t_parsing	parsing;
	// t_ray		ray;
	// t_mlx		mlx;
}				t_data;

typedef struct s_ray
{
	double camera_x;  // pos x sur plan camera entre -1 et 1
	double ray_dir_x; // dir rayon
	double		ray_dir_y;

	int map_x; // case de depart
	int			map_y;

	double side_dist_x; // distances a parcourir avant prochaine frontiere
	double		side_dist_y;

	double delta_dist_x; // cout pr traverser case
	double		delta_dist_y;

	double		perp_wall_dist;
	// distance perpendicullaire entre joueur et mur touche

	int step_x; // sens de deplacement, -1 / +1
	int			step_y;
	int hit;  // indicateur 0/1 mur touche ou pas
	int side; // indicateur type de mur touche (vertical(x) / horizontal(y))
}				t_ray;

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_tex;

typedef struct s_cub
{
	t_player player; // donees
	// t_data	data;
	t_map		map;
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	t_parsing	parsing;
	t_ray		ray;

	void *mlx; // contexte mlx
	void		*win;

	void *img; // images de rendu
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		move_speed;

	t_tex		wall_north;
	t_tex		wall_south;
	t_tex		wall_east;
	t_tex		wall_west;

	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	int			key_e;
}				t_cub;

typedef struct s_draw_data
{
	t_tex		*tex;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		step;
	double		tex_pos;
}				t_draw_data;

// RENDERING
// raycasting.c
void			raycasting(t_cub *cub);
// utils_raycasting.c
void			init_ray(t_cub *cub, t_ray *ray, int x);
void			calc_step_and_side_dist(t_cub *cub, t_ray *ray);
void			perform_dda(t_cub *cub, t_ray *ray);
void			calc_wall_distance(t_ray *ray);
void			init_var(t_cub *cub, t_ray *ray, int x);
void			draw_wall_column(t_cub *cub, int x, int y, int draw_end,
					char tile);
void			draw_wall(t_cub *cub, t_ray *ray, int x);
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

// MOVEMENT
// rot.c
void			rotate_player(t_cub *cub, double rot_speed);
// move_player.c
void			move_forward(t_cub *cub);
void			move_backward(t_cub *cub);
void			move_left(t_cub *cub);
void			move_right(t_cub *cub);
// key_hook.c
int				key_press(int keycode, t_cub *cub);
int				key_release(int keycode, t_cub *cub);
int				update_player(t_cub *cub);
// main.c
int				render_frame(t_cub *cub);
int				close_window(t_cub *cub);
// door.c
void			open_close_door(t_cub *cub);
// spawn.c
void			init_player(t_cub *cub);
void			set_direction(t_cub *cub, char d);

// TEXTURES
// init_textures.c
void			load_textures(t_cub *cub);
t_tex			*get_wall_texture(t_cub *cub, t_ray *ray);

// gnl
int				check(char *str);
char			*extractline(char *s);
char			*clean(char *s);
char			*get_next_line(int fd);
size_t			ft_strlen(const char *str);
char			*read_and_yeah(int fd, char *yeah);
char			*ft_strjoin(char *s1, char const *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);

// parsing
void			normalize_map(t_map *map);
int				is_player(char c);
int				is_walkable(char c);
void			check_map_closed(t_cub *cub);
void			parse_color(t_cub *cub, char *line);
void			check_rgb(t_cub *cub, char **rgb);
int				is_color(char *line);
int				rgb_to_int(int r, int g, int b);
void			set_color(t_cub *cub, char id, char **rgb);
int				is_map_line(char *line);
void			parse_map_line(t_cub *cub, char *line);
char			*ft_strdup(char *s);
char			**add_line(char **grid, char *line);
int				is_texture(char *line);
void			set_texture(t_cub *cub, char *id, char *path);
void			parse_texture(t_cub *cub, char *line);
void			parse_line(t_cub *cub, char *line);
void			parse_cub(t_cub *cub, char *path);
void			set_player(t_cub *cub, char dir, int y, int x);
void			replace_player_by_zero(t_map *map);
void			check_parsing_complete(t_cub *cub);
void			free_tab(char **tab);
void			init_data(t_cub *cub);
void			check_map_char(t_cub *cub);
void			check_map(t_cub *cub);
void			ft_putendl_fd(char *s, int fd);
void			error(t_cub *cub, char *msg);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(const char *s1, const char *set);
int				ft_atoi(char *str);
void			ft_bzero(void *s, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			free_data(t_cub *cub);
int				ft_is_digit(int c);
int				count_tab(char **tab);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
void			free_textures(t_cub *cub);

// mini_map

void			put_pixel(t_cub *cub, int x, int y, int color);
void			draw_square(t_cub *cub, int x, int y, int size, int color);
void			draw_circle(t_cub *cub, int cx, int cy, int radius, int color);
void			draw_player(t_cub *cub);
void			draw_line(t_cub *cub, int x0, int y0, int x1, int y1,
					int color);
void			draw_minimap(t_cub *cub);
#endif