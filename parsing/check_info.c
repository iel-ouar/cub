/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:44:44 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 16:27:13 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

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

t_img	load_img(char *path, void *ptr_mlx)
{
	t_img img;

	ft_bzero(&img, sizeof(img));
	img.img = mlx_xpm_file_to_image(ptr_mlx, path, &img.width, &img.height);
	img.path = path;
	if (!img.img)
	{
		img.valid = -1;	
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	return (img);
}

int	get_textures(t_info *info, t_pars pars)
{
	info->ptr_mlx = mlx_init();
	info->textures.north = load_img(pars.north_tex, info->ptr_mlx);
	if (info->textures.north.valid == -1)
		return (-1);
	info->textures.south = load_img(pars.south_tex, info->ptr_mlx);
	if (info->textures.south.valid == -1)
		return (-1);
	info->textures.west = load_img(pars.west_tex, info->ptr_mlx);
	if (info->textures.west.valid == -1)
		return (-1);
	info->textures.east = load_img(pars.east_tex, info->ptr_mlx);
	if (info->textures.east.valid == -1)
		return (-1);
	return (0);
}

void	full_info(t_info *info, t_pars pars)
{
	info->map = pars.map;
	info->ceiling_colr = pars.ceiling_colr;
	info->floor_colr = pars.floor_colr;
	info->player.x = pars.x_player;
	info->player.y = pars.y_player;
	info->player.dirct = pars.player_dir;
}

void	destroy_images_tex(t_info *info)
{
	if (info->textures.north.img)
		mlx_destroy_image(info->ptr_mlx, info->textures.north.img);
	if (info->textures.south.img)
		mlx_destroy_image(info->ptr_mlx, info->textures.south.img);
	if (info->textures.west.img)
		mlx_destroy_image(info->ptr_mlx, info->textures.west.img);
	if (info->textures.east.img)
		mlx_destroy_image(info->ptr_mlx, info->textures.east.img);
	mlx_destroy_display(info->ptr_mlx);
	free(info->ptr_mlx);
}

int	pars_and_initial(char *av, t_info *info)
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
	if (get_textures(info, pars) == -1)
	{
		destroy_images_tex(info);
		ft_free_pars(&pars, "Error\nTextures is Not valid !!\n");
	}
	full_info(info, pars);
	ft_free_pars(&pars, "Is not Error\n******** ALL GOOD BOSS ********\n");
	return (0);
}
