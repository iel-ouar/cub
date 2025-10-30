/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:17:25 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/30 11:10:16 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_map_body(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	pars->counter = ft_strslen(pars->map);
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (i == 0 && is_player_or_0(pars->map[i][j]))
				return (-1);
			else if (j == 0 && is_player_or_0(pars->map[i][j]))
				return (-1);
			else if (i == pars->counter - 1 && is_player_or_0(pars->map[i][j]))
				return (-1);
			else if (is_player_or_0(pars->map[i][j]) && is_nvalid(
					pars->map[i + 1][j], pars->map[i - 1][j],
						pars->map[i][j + 1], pars->map[i][j - 1]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	player_info(t_pars *pars, char c, int x, int y)
{
	pars->player_dir = c;
	pars->x_player = x;
	pars->y_player = y;
}

int	check_map_element(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	pars->flag = 0;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (is_not_element(pars->map[i][j]) || pars->flag > 1)
				return (-1);
			else if (is_player(pars->map[i][j]))
			{
				pars->flag++;
				player_info(pars, pars->map[i][j], j, i);
			}
			j++;
		}
		i++;
	}
	if (pars->flag == 0)
		return (-1);
	return (0);
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

void	check_data(t_pars *pars)
{
	if (check_color_nbrs(pars) == -1)
		ft_free_pars(pars, "Error\nInvalid value in configuration !\n");
	if (check_map_element(pars) == -1)
		ft_free_pars(pars, "Error\nInvalid character or element in map !\n");
	if (check_map_body(pars) == -1)
		ft_free_pars(pars, "Error\nMap not closed or surrounded by walls\n");
}
