/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:27:25 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/27 19:26:07 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_new_line(char *str, t_pars *pars)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[0] == '\0')
		ft_free_pars(pars, "Error\nMap is Empty !!\n");
	while (str[i])
	{
		if (str[i] != '\n' && flag == 0)
			flag = 1;
		else if (str[i] == '\n' && str[i + 1] == '\n' && flag == 1)
			flag = 2;
		else if (str[i] != '\n' && flag == 2)
		{
			if (str[0] != '\0')
				free(str);
			ft_free_pars(pars, "Error\nMap is not Valid !!\n");
		}
		i++;
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
	else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
		|| line[i] == 'W')
		direction_element(pars, line + i + 1, line[i]);
	else
		problem_element(pars);
}

void	get_elements(int fd, t_pars *pars)
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
	if (line && line[0] != '\0')
		free(line);
	if (pars->count_element == -1)
		line = get_next_line(-2);
}

char	**read_file(int fd, t_pars *pars)
{
	char	*line;
	char	*all_lines;
	char	*tmp;

	get_elements(fd, pars);
	if (pars->count_element != 6)
		ft_free_pars(pars, "Error\nIncorrect element !!\n");
	line = "";
	all_lines = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = all_lines;
		all_lines = ft_strjoin(tmp, line);
		if (tmp[0] != '\0')
			free(tmp);
		free (line);
	}
	free(line);
	close(fd);
	check_new_line(all_lines, pars);
	return (ft_split(all_lines, '\n'));
}
