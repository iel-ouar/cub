/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:48 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/28 16:35:21 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (pars_and_initial(av[1], &game) == -1)
		error_case("Error\n");
	manage_mlx_loops_and_hooks(&game);
}
