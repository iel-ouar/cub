#include "cub.h"

void manage_mlx_loops_and_hooks(t_game *game)
{
	mlx_hook(game->window, 17, 0, close_game, game);
	mlx_hook(game->window, 2, 1L<<0, key_press, &game->player.btn);
	mlx_hook(game->window, 3, 1L<<1, key_release, &game->player.btn);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}