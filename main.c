/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:48 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/08/05 14:27:27 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	error_case(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
	exit(1);
}

int	check_name(char *str)
{
	int	ok;

	ok = 0;
	while (*str && *str != '.')
		str++;
	if (ft_strcmp(str, ".cub") == 0)
		ok = 1;
	return (ok);
}

int	get_fd(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		error_case("Error\nTheir not a file with this name\n");
	return (fd);
}

void	check_last_lines(char *str, int last)
{
	if (str[last] == '\n')
	{
		free(str);
		error_case("Error\nMap is not valid !!\n");
	}
}

// int	count_not_espace(char *line)
// {
// 	int i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (line[i] && line[i] != '\n')
// 	{
// 		if (line[i] != ' ')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// void	color_element(t_data *data, char *line, char c)
// {
// 	if (c == 'F')
// 		data->F = 1;
// 	else
// 		data->C = 1;
	
// }

// void	add_element(t_data *data, char *line)
// {
// 	while (*line == ' ')
// 		line++;
// 	if (line[0] == 'F' || line[0] == 'C')
// 		color_element(data, line, line[0]);
		
	
// }

// void	initial_element(int fd, t_data *data)
// {
// 	char	*line;

// 	line = "";
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		if (line[0] != '\n')
// 			add_element(data, line);
// 	}
	
// }

char	**read_file(int fd, t_data *data)
{
	char	*line;
	char	*all_lines;
	char	*tmp;

	// initial_element(fd, data);
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
	check_last_lines(all_lines, ft_strlen(all_lines) - 1);
	if (all_lines[0] == '\0')
		error_case("Error\nFile is emty\n");
	return (ft_split(all_lines, '\n'));
}

int	pars_and_initial(char *av, t_data *data)
{
	int	fd;

	if (check_name(av) == 0)
		return (-1);
	fd = get_fd(av);
	data->map = read_file(fd, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	ft_bzero(&data, sizeof(data));
	if (pars_and_initial(av[1], &data) == -1)
		error_case("Error\n");
}