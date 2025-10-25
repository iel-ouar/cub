/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:33:21 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 22:01:59 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	is_path(char *str)
{
	int	i;

	i = 0;	
	if (str[i] == '/')
		return (1);
	else if (str[i] == '.')
	{
		i++;
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	add_path_element(t_pars *pars, char *line, char c, char next_c)
{
	int		len;

	len = get_len(line);
	if (c == 'N' && next_c == 'O')
		pars->north_tex = ft_substr(line, 0, len);
	else if (c == 'S' && next_c == 'O')
		pars->south_tex = ft_substr(line, 0, len);
	else if (c == 'E' && next_c == 'A')
		pars->east_tex = ft_substr(line, 0, len);
	else if (c == 'W' && next_c == 'E')
		pars->west_tex = ft_substr(line, 0, len);
	else
		pars->count_element = -1;
}

void	pars_directions(t_pars *pars, char *line, char c, int i)
{
	char	next_c;

	next_c = line[i];
	i++;
	while (line[i] && line[i] != '\n' && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (problem_element(pars));
	if (is_path(line + i))
		add_path_element(pars, line + i, c, next_c);
	else
		pars->count_element = -1;
}

void	direction_element(t_pars *pars, char *line, char c)
{
	int	i;

	i = 0;
	if (c == 'N' && line[i] == 'O')
		pars->no++;
	else if (c == 'S' && line[i] == 'O')
		pars->so++;
	else if (c == 'E' && line[i] == 'A')
		pars->ea++;
	else if (c == 'W' && line[i] == 'E')
		pars->we++;
	if (pars->no > 1 || pars->so > 1 || pars->ea > 1 || pars->we > 1)
		return (problem_element(pars));
	else
		pars_directions(pars, line, c, i);
	if (pars->count_element != -1)
	{
		pars->count_element++;
		pars->counter = 0;
		pars->flag = 0;
	}
}
