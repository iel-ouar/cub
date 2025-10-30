#include "cub.h"


void	rotate_player_view(t_player *player, t_btn *btn)
{
	if (btn->btn_l)
		player->angle += player->rotation;
	else if (btn->btn_r)
		player->angle -= player->rotation;
	player->angle = circular_value(player->angle, 360);
}

bool	is_valid_move(char **map, double map_y, double map_x)
{
	int y;
	int x;
	int safety;

	y = (int)map_y;
	x = (int)map_x;
	safety = 5;
	if (map[(y-safety)/BLOCK][(x)/BLOCK] != '1'
		&& map[(y+safety)/BLOCK][(x)/BLOCK] != '1'
		&& map[(y)/BLOCK][(x-safety)/BLOCK] != '1'
		&& map[(y)/BLOCK][(x+safety)/BLOCK] != '1')
		return (true);
	return (false);
}


double move_on_axis(t_player *player, double value, char axis, char **map)
{
	double y;
	double x;

	y = player->y;
	x = player->x;
	if (axis == 'y')
		y = player->y + value*player->steps;
	else
		x = player->x + value*player->steps;
	if (is_valid_move(map, y, x))
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
