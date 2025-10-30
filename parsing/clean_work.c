/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:41:49 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/30 10:40:25 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	destroy_images_tex(t_game *game)
{
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx, game->textures.south.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx, game->textures.west.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx, game->textures.east.img);
	if (game->image.img)
		mlx_destroy_image(game->mlx, game->image.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	problem_element(t_pars *pars)
{
	pars->count_element = -1;
}

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
	close(pars->fd);
	error_case(str);
}

void	free_game_data(t_game *game)
{
	if (game->map.map)
		ft_free_map(game->map.map);
	if (game->map.map_w)
		free(game->map.map_w);
	if (game->ceiling_colr)
		free(game->ceiling_colr);
	if (game->floor_colr)
		free(game->floor_colr);
	if (game->textures.east.path)
		free(game->textures.east.path);
	if (game->textures.north.path)
		free(game->textures.north.path);
	if (game->textures.west.path)
		free(game->textures.west.path);
	if (game->textures.south.path)
		free(game->textures.south.path);
}
