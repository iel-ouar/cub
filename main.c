/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:48 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 22:15:55 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_pars(t_pars *pars, char *str)
{
	if (pars->map)
		ft_free_map(pars->map);
	if (pars->ceiling_colr)
		free(pars->ceiling_colr);
	if (pars->floor_colr)
		free(pars->floor_colr);
	if (pars->north_tex)
		free(pars->north_tex);
	if (pars->east_tex)
		free(pars->east_tex);
	if (pars->south_tex)
		free(pars->south_tex);
	if (pars->west_tex)
		free(pars->west_tex);
	error_case(str);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (pars_and_initial(av[1], &game) == -1)
		error_case("Error\n");
	init_game(&game, &game.image);
	manage_mlx_loops_and_hooks(&game);
}
