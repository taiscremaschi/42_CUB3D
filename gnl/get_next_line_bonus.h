/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:59:46 by tbolzan-          #+#    #+#             */
/*   Updated: 2023/05/06 18:59:46 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h> /*tam de dados*/
# include <fcntl.h> /*biblioteca para o open*/
# include <stdio.h> /*printf*/
# include <stdlib.h> /*malloc*/
# include <unistd.h> /*read*/
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_check(char *b);

#endif
