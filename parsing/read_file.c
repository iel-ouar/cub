/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:27:25 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/08/19 14:05:38 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_last_lines(char *str, int last)
{
	if (str[last] == '\n')
	{
		free(str);
		error_case("Error\nMap is not valid !!\n");
	}
}

void	add_element(t_pars *pars, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' '))
		color_element(pars, line + i + 1, line[i]);
	else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		direction_element(pars, line + i + 1, line[i]);
	else
		problem_element(pars);
}

void	initial_element(int fd, t_pars *pars)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			add_element(pars, line);
		if (pars->count_element == 6)
			break ;
		else if (pars->count_element == -1)
			break ;
		if (line[0] != '\0')
			free(line);
	}
	if (line[0] != '\0')
		free(line);
	if (pars->count_element == -1)
		line = get_next_line(-2);
}

char	**read_file(int fd, t_pars *pars)
{
	char	*line;
	char	*all_lines;
	char	*tmp;

	initial_element(fd, pars);
	if (pars->count_element != 6)
		ft_free_pars(pars, "Error\nIncorrect element !!\n");
	line = "";
	all_lines = "";
	pars->flag = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line || (line[0] == '\n' && pars->flag == 1))
			break ;
		if (line[0] != '\n')
			pars->flag = 1;
		tmp = all_lines;
		all_lines = ft_strjoin(tmp, line);
		if (tmp[0] != '\0')
			free(tmp);
		free (line);
	}
	free(line);
	close(fd);
	check_last_lines(all_lines, ft_strlen(all_lines) - 1);
	if (all_lines[0] == '\0')
		error_case("Error\nMap is not Valid !\n");
	return (ft_split(all_lines, '\n'));
}
