#include "cub.h"

void	draw_floor_and_seeling(t_game *game)
{
	int y;
	int x;
	int color;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = 0x87CEEB;
		else
			color = 0x895129;
		x = 0;
		while (x < WIDTH)
			put_pixel(&game->image, y, x++, color);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	if (!check_pressing(&game->player.btn))
		return (0);
	clear_frame(&game->image);
	move_player(&game->player, game->map.map);
	// db_draw_map_and_player(game);
	draw_floor_and_seeling(game);
	cast_rays(game, &game->player, &game->map);
	mlx_put_image_to_window(game->mlx, game->window, game->image.img, 0, 0);
	return (0);
}