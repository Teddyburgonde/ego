/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teddybandama <teddybandama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:22:37 by teddybandam       #+#    #+#             */
/*   Updated: 2024/11/03 18:32:02 by teddybandam      ###   ########.fr       */
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

// "je suis la première ligne\nje suis la seconde ligne"

char *extract_line(int fd, char *stock)
{
   char *line;




   return (line); 
}

char *get_next_line(int fd)
{
    static char *stash = NULL;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_line(stash, fd);
    if (!stash)
        return NULL;
    return (stash);
}


