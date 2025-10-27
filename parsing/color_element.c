/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:35:41 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/27 17:29:12 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_nbr_color(char *line)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (i <= 3)
		return (i);
	else
		return (-1);	
}

int	get_nbr(t_pars *pars, int *arry, char *line, int i)
{
	int		len;
	char	*str;

	len = get_nbr_color(line + i);
	if (len == -1)
		return (problem_element(pars), 0);
	else
	{
		str = ft_substr(line, i, len);
		arry[pars->counter] = ft_atoi(str);
		free(str);
		pars->counter++;
		pars->flag = 1;
	}
	return (len - 1);
}

void	check_elem_color(t_pars *pars)
{
	if (pars->counter <= 2)
		problem_element(pars);
}

int	*pars_color(t_pars *pars, char *line, int i)
{
	int		*arry;

	arry = malloc(3 * sizeof(int));
	if (!arry)
		return (NULL);
	while (line[i] && line[i] != '\n' && pars->count_element != -1)
	{
		while (line[i] && line[i] != '\n' && line[i] == ' ')
			i++;
		if (!line[i] || line[i] == '\n')
			break;
		if (ft_isdigit(line[i]) && pars->counter < 3 && pars->flag == 0)
			i = i + get_nbr(pars, arry, line, i);
		else if (line[i] == ',' && pars->counter < 3 && pars->flag == 1)
			pars->flag = 0;
		else if (line[i] != ' ' && line[i] != ','
				&& !ft_isdigit(line[i]))
			return (problem_element(pars), free(arry), NULL);
		else if ((ft_isdigit(line[i]) && pars->flag == 1)
			|| (ft_isdigit(line[i]) && pars->counter >= 3) || (line[i] == ','))
			return (problem_element(pars), free(arry), NULL);
		i++;
	}
	check_elem_color(pars);
	return (arry);
}

void	color_element(t_pars *pars, char *line, char c)
{
	int	i;

	i = 0;
	if (c == 'F')
		pars->f++;
	else
		pars->c++;
	if (pars->c > 1 || pars->f > 1)
	{
		problem_element(pars);
		return ;
	}
	else if (pars->c == 1)
		pars->ceiling_colr = pars_color(pars, line, i);
	else if (pars->f == 1)
		pars->floor_colr = pars_color(pars, line, i);
	if (pars->count_element != -1)
	{
		pars->count_element++;
		pars->counter = 0;
		pars->flag = 0;
	}
}
