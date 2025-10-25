/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:41:49 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 16:27:36 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
			|| c == 'W' || c == 'E')
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

void	problem_element(t_pars *pars)
{
	pars->count_element = -1;
}
