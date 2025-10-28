#include "cub.h"

void	ft_bzero(void *s, size_t n)
{
	char	*tmp_ptr;

	tmp_ptr = (char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = 0;
		n--;
	}
}

void	put_pixel(t_image *image, int y, int x, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = image->addr + (y * image->size_line + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}


double	circular_value(double v1, double v2)
{
	double	result;

	result = fmod(v1, v2);
	if (result < 0)
		result += v2;
	return (result);
}

void	init_ray_struct(t_ray *ray, t_player *player)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->angle = circular_value(player->angle + FOV / 2, 360);
	ray->step = FOV / WIDTH;
}

bool	is_wall(double y, double x, t_map *map)
{
	int (mapY), (mapX);
	mapY = (int)(y/BLOCK);
	mapX = (int)(x/BLOCK);
	if (mapY < 0 || mapY >= map->map_h
	   || mapX < 0 || mapX >= map->map_w[mapY])
		return (true);
	return (map->map[mapY][mapX] == '1');
}