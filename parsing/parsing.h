/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdriouec <sdriouec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:04:28 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/29 19:46:24 by sdriouec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
# define PARCING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_pars
{
	int		flag;
	int		counter;
	int		count_element;
	char	*north_tex;
	char	*west_tex;
	char	*south_tex;
	char	*east_tex;
	int		*floor_colr;
	int		*ceiling_colr;
	int		no;
	int		we;
	int		so;
	int		ea;
	int		f;
	int		c;
	char	**map;
	char	player_dir;
	int		x_player;
	int		y_player;
}	t_pars;

// put_pixel struct
typedef struct s_image
{
	char	*path;
	void	*img;
	char	*addr;
	int		size_line;
	int		endian;
	int		bpp;
	int		width;
	int		height;
	int		valid;
}	t_image;

typedef struct s_textures
{
	t_image		north;
	t_image		west;
	t_image		south;
	t_image		east;
}	t_textures;

// buttons struct
typedef struct s_btn
{
	bool btn_w;
    bool btn_a;
    bool btn_s;
    bool btn_d;
    bool btn_l;
    bool btn_r;
}	t_btn;


// map struct
typedef struct s_map
{
	char **map;
    int *map_w;
    int map_h;
}	t_map;


// player struct
typedef struct s_player
{
	double x;
	double y;
	double angle;
	double rotation;
	double steps;
	t_btn btn;
    t_map *map;
}	t_player;

// game structs
typedef struct s_game
{
    void        *mlx;
    void        *window;
    t_map       map;
    t_player    player;
	t_textures	textures;
	t_image		image;
	int			*floor_colr;
	int			*ceiling_colr;
}   t_game;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_atoi_check(char *str);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	error_case(char *str);

// parsing_functions ****************
int		get_fd(char *str);
int		check_name(char *str);
int		check_data(t_pars *pars);
int		pars_and_initial(char *av, t_game *game);
void	color_element(t_pars *pars, char *line, char c);
void	direction_element(t_pars *pars, char *line, char c);
int		is_nvalid(char down, char up, char right, char left);
int		is_player(char c);
int		is_player_or_0(char c);
int		is_not_element(char c);
void	problem_element(t_pars *pars);
char	**read_file(int fd, t_pars *pars);
void	ft_free_pars(t_pars *pars, char *str);
void	ft_free_map(char **str);
size_t	ft_strslen(char **str);
void	destroy_images_tex(t_game *game);
void	free_game_data(t_game *game);
int		close_game(t_game *game);
void get_player_coord(char **map, t_player *player, double _y, double _x);
#endif