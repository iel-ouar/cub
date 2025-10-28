#ifndef CUB_H
#define CUB_H


// shared libraries headers
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "parsing/parsing.h"

// math macros
#define EPS 1e-9
#define FOV 60.0
#define DEG 57.2958


//  window config
#define WIDTH 1024.0
#define HEIGHT 512.0
#define BLOCK 64.0


// keycodes
#define W 119
#define A 97
#define S 115
#define D 100
#define L 65361
#define R 65363
#define ESC 65307


// horizontal wall struct
typedef struct s_hor
{
    double y;
    double x;
    double hyp;
    double jump;
    double dis;
    double _cos;
    double _sin;
    int color;
}   t_hor;


// verticall wal struct
typedef struct t_ver
{
    double y;
    double x;
    double hyp;
    double jump;
    double dis;
    double _cos;
    double _sin;
    int color;
}   t_ver;


// ray struct
typedef struct s_ray
{
    double angle;
    int    count;
    double step;
    t_hor hor;
    t_ver ver;
}   t_ray;


// helper functions declarations 
// void	init_game(t_game *game, t_image *image);
// void	init_map(t_map *map);
// void	init_player(t_player *player, t_map *map);
void    ft_bzero(void *s, size_t n);
void	manage_mlx_loops_and_hooks(t_game *game);
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_btn *btn);
int		draw_loop(t_game *game);
bool	check_pressing(t_btn *btn);
void    clear_frame(t_image *image);
void    move_player(t_player *player, char **map);
void	db_draw_map_and_player(t_game *game);
void    draw_line(t_game *game, double angle, int distance, int color);
void	cast_rays(t_game *game, t_player *player, t_map *map);
void    init_ray_struct(t_ray *ray, t_player *player);
double	circular_value(double v1, double v2);
bool	is_wall(double y, double x, t_map *map);
void    draw_block(t_game *game, int y, int x, int color);
void    put_pixel(t_image *image, int y, int x, int color);
void	draw_wall(t_game *game, t_ray *ray, double distance, int color);

#endif