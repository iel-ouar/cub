/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:13:48 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/08/14 17:13:51 by iel-ouar         ###   ########.fr       */
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

void	problem_element(t_data *data)
{
	data->count_element = -1;
}

int	count_not_espace(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*tmp;
// 	size_t	i;
// 	size_t	l;

// 	if (!s)
// 		return (NULL);
// 	l = ft_strlen(s);
// 	if (start >= l)
// 		return (ft_strdup(""));
// 	if (len > l - start)
// 		len = l - start;
// 	tmp = (char *)malloc (len + 1);
// 	if (!tmp)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		tmp[i] = s[start + i];
// 		i++;
// 	}
// 	tmp[i] = '\0';
// 	return (tmp);
// }

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

int	get_nmbr(t_data *data, int *arry, char *line, int i)
{
	int	len;

	len = get_nbr_color(line + i);
	if (len == -1)
		return (problem_element(data), 0);
	else
	{
		arry[data->counter] = ft_atoi(ft_substr(line, i, len));
		data->counter++;
		data->flag = 1;
	}
	return (len - 1);
}

//F    9 9,     88      58,                5    , 255         \n

int	*pars_color(t_data *data, char *line, int i)
{
	int		*arry;

	arry = malloc(3 * sizeof(int));
	if (!arry)
		return (NULL);
	while (line[i] && line[i] != '\n' && data->count_element != -1)
	{
		while (line[i] && line[i] != '\n' && line[i] == ' ')
			i++;
		if (!line[i] || line[i] == '\n')
			break;
		if (ft_isdigit(line[i]) && data->counter < 3 && data->flag == 0)
			i = i + get_nmbr(data, arry, line, i);
		else if (line[i] == ',' && data->counter < 3 && data->flag == 1)
			data->flag = 0;
		else if (line[i] != ' ' && line[i] != ','
				&& !ft_isdigit(line[i]))
			return (problem_element(data), free(arry), NULL);
		else if ((ft_isdigit(line[i]) && data->flag == 1)
			|| (ft_isdigit(line[i]) && data->counter >= 3) || (line[i] == ','))
			return (problem_element(data), free(arry), NULL);
		i++;
	}
	return (arry);
}

void	color_element(t_data *data, char *line, char c)
{
	int	i;

	i = 0;
	if (c == 'F')
		data->f++;
	else
		data->c++;
	if (data->c > 1 || data->f > 1)
	{
		problem_element(data);
		return ;
	}
	else if (data->c == 1)
		data->ceiling_colr = pars_color(data, line, i);
	else if (data->f == 1)
		data->floor_colr = pars_color(data, line, i);
	if (data->count_element != -1)
	{
		data->count_element++;
		data->counter = 0;
		data->flag = 0;
	}
}

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

void	add_path_element(t_data *data, char *line, char c, char next_c)
{
	int		len;

	len = get_len(line);
	if (c == 'N' && next_c == 'O')
		data->north_tex = ft_substr(line, 0, len);
	else if (c == 'S' && next_c == 'O')
		data->south_tex = ft_substr(line, 0, len);
	else if (c == 'E' && next_c == 'A')
		data->east_tex = ft_substr(line, 0, len);
	else if (c == 'W' && next_c == 'E')
		data->west_tex = ft_substr(line, 0, len);
	else
		data->count_element = -1;
}

void	pars_directions(t_data *data, char *line, char c, int i)
{
	char	next_c;

	next_c = line[i];
	i++;
	while (line[i] && line[i] != '\n' && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (problem_element(data));
	if (is_path(line + i))
		add_path_element(data, line + i, c, next_c);
	else
		data->count_element = -1;
}

void	direction_element(t_data *data, char *line, char c)
{
	int	i;

	i = 0;
	if (c == 'N' && line[i] == 'O')
		data->no++;
	else if (c == 'S' && line[i] == 'O')
		data->so++;
	else if (c == 'E' && line[i] == 'A')
		data->ea++;
	else if (c == 'W' && line[i] == 'E')
		data->we++;
	if (data->no > 1 || data->so > 1 || data->ea > 1 || data->we > 1)
		return (problem_element(data));
	else
		pars_directions(data, line, c, i);
	if (data->count_element != -1)
	{
		data->count_element++;
		data->counter = 0;
		data->flag = 0;
	}
}

void	add_element(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' '))
		color_element(data, line + i + 1, line[i]);
	else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		direction_element(data, line + i + 1, line[i]);
	else
		problem_element(data);
}

void	initial_element(int fd, t_data *data)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			add_element(data, line);
		if (data->count_element == 6)
			break ;
		else if (data->count_element == -1)
			break ;
		if (line[0] != '\0')
			free(line);
	}
	if (line[0] != '\0')
		free(line);
}

char	**read_file(int fd, t_data *data)
{
	char	*line;
	char	*all_lines;
	char	*tmp;

	initial_element(fd, data);
	if (data->count_element != 6)
		error_case("Error\nIncorrect data in File !!!!\n");
	line = "";
	all_lines = "";
	data->flag = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line || (line[0] == '\n' && data->flag == 1))
			break ;
		if (line[0] != '\n')
			data->flag = 1;
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
		error_case("Error\nMap is not Valid\n");
	return (ft_split(all_lines, '\n'));
}

int	check_color_nbrs(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (data->ceiling_colr[i] > 255 || data->ceiling_colr[i] < 0)
			return (-1);
		if (data->floor_colr[i] > 255 || data->floor_colr[i] < 0)
			return (-1);
		i++;
	}
	return (0);
}

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

int	check_map_element(t_data *data)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_not_element(data->map[i][j]) || p > 1)
				return (-1);
			else if (is_player(data->map[i][j]))
				p++;
			j++;
		}
		i++;
	}
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

int	count_height(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_map_body(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->counter = count_height(data->map) - 1;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (i == 0 && (data->map[i][j] == '0' || is_player(data->map[i][j])))
				return (-1);
			else if (j == 0 && (data->map[i][j] == '0' || is_player(data->map[i][j])))
				return (-1);
			else if (i == data->counter && (data->map[i][j] == '0' || is_player(data->map[i][j])))
				return (-1);
			else if ((data->map[i][j] == '0' || is_player(data->map[i][j]))
				&& is_nvalid(data->map[i + 1][j], data->map[i - 1][j], data->map[i][j + 1], data->map[i][j - 1]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_data(t_data *data)
{
	if (check_color_nbrs(data) == -1)
		return (-1);
	if (check_map_element(data) == -1)
		return (-1);
	if (check_map_body(data) == -1)
		return (-1);
	return (0);
}

int	pars_and_initial(char *av, t_data *data)
{
	int	fd;

	if (check_name(av) == 0)
		return (-1);
	fd = get_fd(av);
	data->map = read_file(fd, data);
	if (check_data(data) == -1)
		error_case("Error\n Waaa 5oya xHad Lmap Dyal BraHex\n");
	else
		printf("Map Nadya b7al wejhek :)\n");
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