/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:58:58 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/01/04 17:49:51 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

char	*get_next_line(int fd);
int		where_is_nl(char *s);
char	*gnl_cat(char **line, char *buf);
char	*gnl_line(char **line, int lu);
char	*gnl_eof(char **line);
char	*gnl_free(char **s1, char *s2);

#endif
