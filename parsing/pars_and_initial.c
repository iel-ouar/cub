/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_and_initial.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:44:44 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/28 17:09:38 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_image	load_img(char *path, void *ptr_mlx)
{
	t_image	img;

	ft_bzero(&img, sizeof(img));
	img.img = mlx_xpm_file_to_image(ptr_mlx, path, &img.width, &img.height);
	img.path = path;
	if (!img.img)
	{
		img.valid = -1;
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.size_line, &img.endian);
	return (img);
}

int	get_textures(t_game *game, t_pars pars)
{
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
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!game->window)
		return (-1);
	game->image.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image.img)
		return (-1);
	game->image.addr = mlx_get_data_addr(game->image.img, &game->image.bpp,
		&game->image.size_line, &game->image.endian);
	if (!game->image.addr)
		return (-1);
	return (0);
}

int	get_the_angle(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'S')
		return (270);
	else if (c == 'W')
		return (180);
	return (0);
}

void	init_game(t_game *game, t_pars pars)
{
	pars.flag = 0;
	game->map.map = pars.map;
	game->map.map_h = pars.counter;
	game->map.map_w = malloc((game->map.map_h + 1) * sizeof(int));
	if (!game->map.map_w)
	{
		destroy_images_tex(game);
		ft_free_pars(&pars, "Error\nMalloc failed !\n");
	}
	while (pars.flag < game->map.map_h)
	{
		game->map.map_w[pars.flag] = ft_strlen(game->map.map[pars.flag]);
		pars.flag++;
	}
	game->ceiling_colr = pars.ceiling_colr;
	game->floor_colr = pars.floor_colr;
	game->player.x = pars.x_player * BLOCK;
	game->player.y = pars.y_player * BLOCK;
	game->player.angle = get_the_angle(pars.player_dir);
	game->player.rotation = 0.6;
	game->player.steps = 1;
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
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_free_pars(&pars, "Error\nConnection faild\n");
	if (get_textures(game, pars) == -1)
	{
		destroy_images_tex(game);
		ft_free_pars(&pars, "Error\nTextures is Not valid !!\n");
	}
	init_game(game, pars);
	game->player.map = &game->map;
	ft_bzero(&game->player.btn, sizeof(t_btn));
	return (0);
}
