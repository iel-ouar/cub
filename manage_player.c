#include "cub.h"

void	init_player(t_player *player, t_map *map)
{
	player->y = BLOCK; 
	player->x = BLOCK;
	player->angle = 320;
	player->rotation = 0.6;
	player->steps = 1;
	player->map = map;
	ft_bzero(&player->btn, sizeof(t_btn));
}


void	rotate_player_view(t_player *player, t_btn *btn)
{
	if (btn->btn_l)
		player->angle += player->rotation;
	else if (btn->btn_r)
		player->angle -= player->rotation;
	player->angle = circular_value(player->angle, 360);
}



double move_on_axis(t_player *player, double value, char axis, char **map)
{
	double y;
	double x;
	int map_y;
	int map_x;

	y = player->y;
	x = player->x;
	if (axis == 'y')
		y = player->y + value*player->steps;
	else
		x = player->x + value*player->steps;
	map_y = y/BLOCK;
	map_x = x/BLOCK;
	if (map[map_y][map_x] != '1')
	{
		if (axis == 'y')
			return (y);
		return (x);
	}
	if (axis == 'y')
		return (player->y);
	return (player->x);
}


void	move_player(t_player *player, char **map)
{
	double sin_cos[2];

	sin_cos[0] = sin(player->angle/DEG);
	sin_cos[1] = cos(player->angle/DEG);
	rotate_player_view(player, &player->btn);
	if (player->btn.btn_w)
	{
		player->y = move_on_axis(player, -sin_cos[0], 'y', map);
		player->x = move_on_axis(player, sin_cos[1], 'x', map);
	}
	else if (player->btn.btn_s)
	{
		player->y = move_on_axis(player, sin_cos[0], 'y', map);
		player->x = move_on_axis(player, -sin_cos[1], 'x', map);
	}
	else if (player->btn.btn_d)
	{
		player->y = move_on_axis(player, sin_cos[1], 'y', map);
		player->x = move_on_axis(player, sin_cos[0], 'x', map);
	}
	else if (player->btn.btn_a)
	{
		player->y = move_on_axis(player, -sin_cos[1], 'y', map);
		player->x = move_on_axis(player, -sin_cos[0], 'x', map);
	}
}
