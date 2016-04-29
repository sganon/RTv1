/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 14:47:44 by sganon            #+#    #+#             */
/*   Updated: 2016/04/29 14:50:44 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *s, int fd)
{
	ft_putstr_fd(ANSI_COLOR_RED, fd);
	ft_putendl_fd(s, fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
	exit(EXIT_FAILURE);
}
