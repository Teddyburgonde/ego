/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teddybandama <teddybandama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:22:37 by teddybandam       #+#    #+#             */
/*   Updated: 2024/11/03 21:58:12 by teddybandam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>


static char *read_line(char *stash, int fd)
{
    char *buff;
    int byte_read;

    byte_read = 1;
    if (stash == NULL)
    {
        stash = malloc(1);
        if (!stash)
            return (NULL);
        stash[0] = '\0';
    }
    buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buff)
    {
        free(stash);
        return (NULL);
    }
    // lecture jusqu'a qu'il trouve un '\n'
    while (byte_read > 0 && ft_strchr(stash, '\n') == NULL)
    {
        byte_read = read(fd, buff, BUFFER_SIZE);
        if (byte_read < 0)
        {
            free(buff);
			free(stash);
			return (NULL);
        }
        buff[byte_read] = '\0';
        stash = ft_strjoin(stash, buff);
        if (!stash)
        {
            free(buff);
            return (NULL);
        }
    }
    free(buff);
    return (stash);
}

// "debug je suis ici"
char *extract_line(char *stash)
{
    char *line;
    int i;
    int line_length;

    i = 0;

    if (!stash[i])
        return (NULL);
    // ici debug
    while (stash[i] && stash[i] != '\n')
        i++;
    line_length = i;
    if (stash[i] == '\n')
        line_length++;
    line = ft_substr(stash, 0, line_length);
    return (line); 
}

char *extract_surplus_line(char *stash)
{
    int i;
    int j;

    j = 0;
    char    *surplus_line;

    if (!stash)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] != '\n')
        return (NULL);
    surplus_line = malloc(sizeof(char) * (ft_strlen(stash) - i));
    if (!surplus_line)
        return (NULL);
    i++;
    while (stash[i])
    {
        surplus_line[j] = stash[i]; 
        i++;
        j++;
    }
    if (stash[i] != '\n') 
    {
        free(stash);
        return (NULL);
    }
    surplus_line[j] = '\0';
    free(stash);
    return (surplus_line);
}

char *get_next_line(int fd)
{
    static char *stash = NULL;
    char *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_line(stash, fd);
    if (!stash)
        return NULL;
    line = extract_line(stash);
    stash = extract_surplus_line(stash);
    return (line);
}

#include <stdio.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
    if (fd1 < 0)
        return (1);
	i = 1;
	while (1)
	{
        line = get_next_line(fd1);
        if (line == NULL)
            break;
        printf("line [%02d]: %s", i, line);
        free(line);
	    i++;
	}
	close(fd1);
	return (0);
}