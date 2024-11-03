/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teddybandama <teddybandama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:22:37 by teddybandam       #+#    #+#             */
/*   Updated: 2024/11/03 15:05:29 by teddybandam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_line(char *stash, int fd)
{
    char *buff;
    int byte_read;

    byte_read = 1;
    buff = NULL;
    if (stash != NULL)
    {
        buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
        if (!buff)
            return (NULL);
        byte_read = read(fd, buff, BUFFER_SIZE);
        buff[byte_read] = '\0';
        if (byte_read > 1)
        {
            stash = ft_strjoin(stash, buff);
            free(buff);
            return (NULL);
        }
        free(buff);
        buff = NULL; 
    }
    else
    {
        stash = malloc(sizeof(char));
        if (!stash)
            return (NULL);
        stash[0] = '\0';
    }
    // byte_read > 0 tant qu'il reste des donnees a lire 
    buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buff)
    {
        if (stash)
            free(stash);
        return (NULL);
    }
    // lecture jusqu'a qu'il trouve un '\n'
    while (byte_read > 0 && ft_strchr(buff, '\n') == NULL)
    {
        byte_read = read(fd, buff, BUFFER_SIZE);
    }
}

char *get_next_line(int fd)
{
    static char *stash = NULL;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_line();
    return (stash);
}