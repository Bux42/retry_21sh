/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:31:21 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/11 17:31:22 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	errexit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	print_access_error(char *fullpath)
{
	if (access(fullpath, X_OK))
		ft_putstr_fd("Permission denied.\n", 2);
	else
		ft_putstr_fd("error\n", 2);
}
