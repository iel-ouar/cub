/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:48 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/30 10:26:20 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	close_game(t_game *game)
{
	destroy_images_tex(game);
	free_game_data(game);
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (pars_and_initial(av[1], &game) == -1)
		error_case("Error\nCannot open .cub file\n");
	manage_mlx_loops_and_hooks(&game);
}
