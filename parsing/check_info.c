/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:44:44 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/08/19 14:08:21 by iel-ouar         ###   ########.fr       */
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
		printf("%d\n",pars->ceiling_colr[i]);
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

void	full_info(t_info *info, t_pars pars)
{
	info->map = pars.map;
	info->ceiling_colr = pars.ceiling_colr;
	info->floor_colr = pars.floor_colr;
	info->east_tex = pars.east_tex;
	info->north_tex = pars.north_tex;
	info->south_tex = pars.south_tex;
	info->west_tex = pars.west_tex;
	info->player.x = pars.x_player;
	info->player.y = pars.y_player;
	info->player.dirct = pars.player_dir;
}

int	pars_and_initial(char *av, t_info *info)
{
	t_pars	pars;
	int		fd;

	(void)info;
	if (check_name(av) == 0)
		return (-1);
	fd = get_fd(av);
	ft_bzero(&pars, sizeof(pars));
	pars.map = read_file(fd, &pars);
	if (check_data(&pars) == -1)
		ft_free_pars(&pars, "Error\nIncorrect argument in File !!");
	ft_free_pars(&pars, "Is not Error\n******** ALL GOOD BOSS ********\n");
	// full_info(info, pars);
	return (0);
}
