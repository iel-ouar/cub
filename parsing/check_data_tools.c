/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:22:00 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/27 19:44:39 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
			|| c == 'W' || c == 'E')
			return (1);
	return (0);
			
}

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

int	is_not_element(char c)
{
	if (c != ' ' && c != '1' && c != '0' && c != 'N'
			&& c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	is_player_or_0(char c)
{
	if (c == '0' || is_player(c))
		return (1);
	return (0);
}
