/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:44:44 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/26 15:04:42 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	count_not_espace(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

int	check_color_nbrs(t_pars *pars)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (pars->ceiling_colr[i] > 255 || pars->ceiling_colr[i] < 0)
			return (-1);
		if (pars->floor_colr[i] > 255 || pars->floor_colr[i] < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	check_data(t_pars *pars)
{
	if (check_color_nbrs(pars) == -1)
		return (-1);
	if (check_map_element(pars) == -1)
		return (-1);
	if (check_map_body(pars) == -1)
		return (-1);
	return (0);
}

t_image	load_img(char *path, void *ptr_mlx)
{
	t_image img;

	ft_bzero(&img, sizeof(img));
	img.img = mlx_xpm_file_to_image(ptr_mlx, path, &img.width, &img.height);
	img.path = path;
	if (!img.img)
	{
		img.valid = -1;	
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	return (img);
}

int	get_textures(t_game *game,t_pars pars)
{
	game->mlx = mlx_init();
	game->textures.north = load_img(pars.north_tex, game->mlx);
	if (game->textures.north.valid == -1)
		return (-1);
	game->textures.south = load_img(pars.south_tex, game->mlx);
	if (game->textures.south.valid == -1)
		return (-1);
	game->textures.west = load_img(pars.west_tex, game->mlx);
	if (game->textures.west.valid == -1)
		return (-1);
	game->textures.east = load_img(pars.east_tex, game->mlx);
	if (game->textures.east.valid == -1)
		return (-1);
	return (0);
}

void	full_info(t_game *game, t_pars pars)
{
	int	i;

	i = 0;
	game->map.map = pars.map;
	game->map.map_h = ft_strslen(game->map.map);
	game->map.map_w = malloc((game->map.map_h + 1) * sizeof(int));
	if (!game->map.map_w)
	{
		destroy_images_tex(game);
		ft_free_pars(&pars, "Error\nMalloc failed !\n");	
	}
	while (i < game->map.map_h)
	{
		game->map.map_w[i] = ft_strlen(game->map.map[i]);
		i++;
	}
	game->ceiling_colr = pars.ceiling_colr;
	game->floor_colr = pars.floor_colr;
	game->player.x = pars.x_player * BLOCK;
	game->player.y = pars.y_player * BLOCK;
	game->player.direct = pars.player_dir;
	game->player.angle = 320;
	game->player.rotation = 0.6;
	game->player.steps = 1;
}

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
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	pars_and_initial(char *av, t_game *game)
{
	t_pars	pars;
	int		fd;

	if (check_name(av) == 0)
		return (-1);
	fd = get_fd(av);
	ft_bzero(&pars, sizeof(pars));
	pars.map = read_file(fd, &pars);
	if (check_data(&pars) == -1)
		ft_free_pars(&pars, "Error\nIncorrect argument in File !!\n");
	if (get_textures(game, pars) == -1)
	{
		destroy_images_tex(game);
		ft_free_pars(&pars, "Error\nTextures is Not valid !!\n");
	}
	full_info(game, pars);
	game->player.map = &game->map;
	ft_bzero(&game->player.btn, sizeof(t_btn));
	return (0);
}
