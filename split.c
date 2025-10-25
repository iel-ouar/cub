/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ouar <iel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:34:59 by iel-ouar          #+#    #+#             */
/*   Updated: 2025/10/25 22:01:11 by iel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	b;
	int	i;

	i = 0;
	count = 0;
	b = 0;
	while (s[i])
	{
		if (s[i] != c && b == 0)
		{
			b = 1;
			count++;
		}
		else if (s[i] == c)
			b = 0;
		i++;
	}
	return (count);
}

static void	ft_free_p(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

static char	*get_next_word(char *s, char c, size_t *j)
{
	unsigned int	start;
	size_t			len;
	size_t			i;

	i = *j;
	while (s[i] && s[i] == c)
		i++;
	start = i;
	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	*j = i;
	return (ft_substr(s, start, len));
}

char	**ft_split(char *s, char c)
{
	char	**tmp;
	size_t	i;
	size_t	count;
	size_t	j;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	tmp = (char **)malloc((count + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		tmp[i] = get_next_word(s, c, &j);
		if (!tmp[i])
		{
			ft_free_p(tmp, i);
			return (NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (free(s), tmp);
}
