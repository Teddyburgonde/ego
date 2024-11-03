/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teddybandama <teddybandama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:28:29 by teddybandam       #+#    #+#             */
/*   Updated: 2024/11/03 14:45:04 by teddybandam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H

#include <stdlib.h>
#define BUFFER_SIZE 5
 
char *get_next_line(int fd);
int	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);


#endif 