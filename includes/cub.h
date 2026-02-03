/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:35:57 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/21 20:23:18 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef CUB_H
// # define CUB_H

// # include <fcntl.h>
// # include <stddef.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <unistd.h>

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 1024
// # endif

// typedef struct s_map
// {
// 	char		**grid;
// 	int			width;
// 	int			height;
// }				t_map;

// typedef struct s_parsing
// {
// 	int			in_map;
// 	int			map_finished;
// }				t_parsing;

// typedef struct s_texture
// {
// 	char *path; // Chemin vers le .xpm
// 	void *img;  // Image MLX
// 	int			width;
// 	int			height;
// 	int *addr; // Pixels
// }				t_texture;

// typedef struct s_player
// {
// 	double x;       // pos sur l'axe X
// 	double y;       // pos sur l'axe Y
// 	double dir_x;   // vecteur dir regard (x)
// 	double dir_y;   // vecteur dir regard Y
// 	double plane_x; // vecteur camera x
// 	double plane_y; // vecteur camera y
// 	char		start_dir;
// }				t_player;

// enum			e_tex
// {
// 	NO,
// 	SO,
// 	WE,
// 	EA
// };

// typedef struct s_data
// {
// 	t_map		map;
// 	t_texture	textures[4];
// 	int			floor_color;
// 	int			ceiling_color;
// 	t_player	player;
// 	t_parsing	parsing;
// 	// t_ray		ray;
// 	// t_mlx		mlx;
// }				t_data;

// // gnl
// int				check(char *str);
// char			*extractline(char *s);
// char			*clean(char *s);
// char			*get_next_line(int fd);
// size_t			ft_strlen(const char *str);
// char			*read_and_yeah(int fd, char *yeah);
// char			*ft_strjoin(char *s1, char const *s2);
// void			*ft_memcpy(void *dest, const void *src, size_t n);

// // parsing
// void			normalize_map(t_map *map);
// int				is_player(char c);
// int				is_walkable(char c);
// void			check_map_closed(t_data *data);
// void			parse_color(t_data *data, char *line);
// void			check_rgb(t_data *data, char **rgb);
// int				is_color(char *line);
// int				rgb_to_int(int r, int g, int b);
// void			set_color(t_data *data, char id, char **rgb);
// int				is_map_line(char *line);
// void			parse_map_line(t_data *data, char *line);
// char			*ft_strdup(char *s);
// char			**add_line(char **grid, char *line);
// int				is_texture(char *line);
// void			set_texture(t_data *data, char *id, char *path);
// void			parse_texture(t_data *data, char *line);
// void			parse_line(t_data *data, char *line);
// void			parse_cub(t_data *data, char *path);
// void			set_player(t_data *data, char dir, int y, int x);
// void			replace_player_by_zero(t_map *map);
// void			check_parsing_complete(t_data *data);
// void			free_tab(char **tab);
// void			init_data(t_data *data);
// void			check_map_char(t_data *data);
// void			check_map(t_data *data);
// void			ft_putendl_fd(char *s, int fd);
// void			error(t_data *data, char *msg);
// char			**ft_split(char const *s, char c);
// char			*ft_strtrim(const char *s1, const char *set);
// int				ft_atoi(char *str);
// void			ft_bzero(void *s, size_t n);
// int				ft_strncmp(const char *s1, const char *s2, size_t n);
// void			free_data(t_data *data);
// int				ft_is_digit(int c);
// int				count_tab(char **tab);
// char			*ft_strchr(const char *s, int c);
// int				ft_strcmp(const char *s1, const char *s2);

// #endif