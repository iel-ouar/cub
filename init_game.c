#include "cub.h"

void init_game(t_game *game, t_image *image)
{
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
		&image->size_line, &image->endian);
	// init_map(&game->map);
	// init_player(&game->player, &game->map);
}