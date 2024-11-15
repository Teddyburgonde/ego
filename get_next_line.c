/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:22:37 by teddybandam       #+#    #+#             */
/*   Updated: 2024/11/04 19:00:49 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_concatenate(int fd, char *stash)
{
	char	*buff;
	int		byte_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(stash);
		return (NULL);
	}
	byte_read = read(fd, buff, BUFFER_SIZE);
	if (byte_read < 0)
	{
		free(buff);
		return (NULL);
	}
	buff[byte_read] = '\0';
	stash = ft_strjoin(stash, buff);
	if (!stash)
	{
		free(buff);
		return (NULL);
	}
	free(buff);
	return (stash);
}

static char	*read_line(char *stash, int fd)
{
	char	*new_stash;

	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	while (ft_strchr(stash, '\n') == NULL)
	{
		new_stash = read_and_concatenate(fd, stash);
		if (!new_stash)
		{
			free(stash);
			return (NULL);
		}
		stash = new_stash;
		if (stash[0] == '\0')
			break ;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		line_length;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line_length = i;
	if (stash[i] == '\n')
		line_length++;
	line = ft_substr(stash, 0, line_length);
	return (line);
}

static char	*extract_surplus_line(char *stash)
{
	char	*surplus_line;
	int		i;
	int		j;

	j = 0;
	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	j = ft_strlen(stash);
	if (i == j)
	{
		free(stash);
		return (NULL);
	}
	surplus_line = ft_substr(stash, i, j);
	if (!surplus_line)
		return (NULL);
	free(stash);
	return (surplus_line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(stash, fd);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = extract_surplus_line(stash);
	return (line);
}
