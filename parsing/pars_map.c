/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:40 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 22:02:02 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_nvalid(char down, char up, char right, char left)
{
	if (down == ' ' || down == '\0')
		return (1);
	else if (up == ' ' || up == '\0')
		return (1);
	else if (right == ' ' || right == '\0')
		return (1);
	else if (left == ' ' || left == '\0')
		return (1);
	return (0);
}

int	check_map_element(t_pars *pars)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (is_not_element(pars->map[i][j]) || p > 1)
				return (-1);
			else if (is_player(pars->map[i][j]))
			{
				p++;
				pars->player_dir = pars->map[i][j];
				pars->x_player = j;
				pars->y_player = i;
			}
			j++;
		}
		i++;
	}
	if (p == 0)
		return (-1);
	return (0);
}

int	check_map_body(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	pars->counter = count_height(pars->map) - 1;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (i == 0 && (pars->map[i][j] == '0' || is_player(pars->map[i][j])))
				return (-1);
			else if (j == 0 && (pars->map[i][j] == '0' || is_player(pars->map[i][j])))
				return (-1);
			else if (i == pars->counter && (pars->map[i][j] == '0' || is_player(pars->map[i][j])))
				return (-1);
			else if ((pars->map[i][j] == '0' || is_player(pars->map[i][j]))
				&& is_nvalid(pars->map[i + 1][j], pars->map[i - 1][j], pars->map[i][j + 1], pars->map[i][j - 1]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
