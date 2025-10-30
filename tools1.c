/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdriouec <sdriouec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:23:02 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/29 19:55:53 by sdriouec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sing;
	int	n;

	n = 0;
	sing = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sing = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sing);
}

int	ft_atoi_check(char *str)
{
	long	i;
	int		sing;
	long	n;

	n = 0;
	sing = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sing = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		if ((sing == -1 && (-n) < (-2147483648))
			|| (sing == 1 && n > 2147483647))
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strslen(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

void get_player_coord(char **map, t_player *player, double _y, double _x)
{
	int y;
	int x;

	y = _y;
	x = _x;
	if (map[y-1][x] == '1')
		player->y = y * BLOCK * 2 - 1;
	else
		player->y = y * BLOCK;
	if (map[y][x-1] == '1')
		player->x = x * BLOCK * 2 - 1;
	else
		player->x = x * BLOCK;
	}