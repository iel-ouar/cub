#include "cub.h"

void draw_block(t_game *game, int y, int x, int color)
{
	int j;
	int i;

	j = 0;
	while (j < BLOCK)
	{
		i = 0;
		while (i < BLOCK)
		{
			put_pixel(&game->image, BLOCK*y+j, BLOCK*x+i, color);
			i++;
		}
		j++;
	}
}


void	db_draw_map_and_player(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '1')
				draw_block(game, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	draw_line(game, game->player.angle, 10, 0xFF00FF);
}

void clear_frame(t_image *image)
{
	int i;
	int j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			put_pixel(image, j, i, 0x000000);
			i++;
		}
		j++;
	}
}

void draw_line(t_game *game, double angle, int distance, int color)
{
    int i;

	i = 0;
    while (i < distance)
    {
        put_pixel(&game->image, game->player.y - sin(angle/DEG) * i,
        game->player.x + cos(angle/DEG) * i, color);
        i++;
    }
}

void	draw_wall(t_game *game, t_ray *ray, double distance, int color)
{
	double	corrected_dist;
	double	dist_plane;
	double	wall_height;
	double	wall_start;
	int		y;

	corrected_dist = distance * cos((ray->angle - game->player.angle) / DEG);
	dist_plane = (HEIGHT / 2.0) / tan((FOV / 2.0) / DEG);
	wall_height = (BLOCK * dist_plane) / corrected_dist;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	wall_start = (HEIGHT - wall_height) / 2.0;
	if (wall_start < 0)
		wall_start = 0;
	y = 0;
	while (y < wall_height)
		put_pixel(&game->image, wall_start + y++, ray->count, color);
}