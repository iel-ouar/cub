# include "cub.h"

double	find_horizontal_wall(t_ray *ray, t_player *player, t_map *map)
{
	ray->hor._sin = -sin(ray->angle/DEG);
	ray->hor._cos = cos(ray->angle/DEG);
	ray->hor.jump = BLOCK;
	ray->hor.color = 0x0000FF;
	ray->hor.y = floor(player->y / BLOCK) * BLOCK + BLOCK ;
	if (ray->hor._sin < 0)
	{
		ray->hor.color = 0x00FF00;
		ray->hor.jump = -BLOCK;
		ray->hor.y = floor(player->y / BLOCK) * BLOCK - EPS;
	}
	ray->hor.hyp = (ray->hor.y - player->y) / ray->hor._sin;
	ray->hor.x = player->x + ray->hor.hyp * ray->hor._cos;
	while (!is_wall(ray->hor.y, ray->hor.x, map))
	{
		ray->hor.y += ray->hor.jump;
		ray->hor.hyp = (ray->hor.y - player->y) / ray->hor._sin;
		ray->hor.x = player->x + ray->hor.hyp * ray->hor._cos;
	}
	return (ray->hor.hyp);
}

double	find_vertical_wall(t_ray *ray, t_player *player, t_map *map)
{
	ray->ver._sin = -sin(ray->angle/DEG);
	ray->ver._cos = cos(ray->angle/DEG);
	ray->ver.jump = BLOCK;
	ray->ver.color = 0xFF0000;
	ray->ver.x = floor(player->x / BLOCK) * BLOCK + BLOCK ;
	if (ray->ver._cos < 0)
	{
		ray->ver.color = 0xFFFF00;
		ray->ver.jump = -BLOCK;
		ray->ver.x = floor(player->x / BLOCK) * BLOCK - EPS;
	}
	ray->ver.hyp = (ray->ver.x - player->x) / ray->ver._cos;
	ray->ver.y = player->y + ray->ver.hyp * ray->ver._sin;
	while (!is_wall(ray->ver.y, ray->ver.x, map))
	{
		ray->ver.x += ray->ver.jump;
		ray->ver.hyp = (ray->ver.x - player->x) / ray->ver._cos;
		ray->ver.y = player->y + ray->ver.hyp * ray->ver._sin;
	}
	return (ray->ver.hyp);
}



void cast_rays(t_game *game, t_player *player, t_map *map)
{
	t_ray ray;
	init_ray_struct(&ray, player);
	while (ray.count < WIDTH)
	{
		if (ray.angle != 0 && ray.angle != 180)
			ray.hor.dis = find_horizontal_wall(&ray, player, map);
		if (ray.angle != 90 && ray.angle != 270)
			ray.ver.dis = find_vertical_wall(&ray, player, map);
		if (ray.hor.dis <= ray.ver.dis)
			draw_wall(game, &ray, ray.hor.dis, ray.hor.color);
		else
			draw_wall(game, &ray, ray.ver.dis, ray.ver.color);
		ray.angle -= ray.step;
		ray.count++;
	}
}