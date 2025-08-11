/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:04:28 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/08/11 15:06:39 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"

typedef struct s_data
{
	int		flag;
	int		counter;
	int		count_element;
	char	*north_tex;
	char	*west_tex;
	char	*south_tex;
	char	*east_tex;
	int		*floor_colr;
	int		*ceiling_colr;
	int		no;
	int		we;
	int		so;
	int		ea;
	int		f;
	int		c;
	char	**map;
	char	player_dir;
}	t_data;


int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_atoi_check(char *str);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char *s, char c);

#endif