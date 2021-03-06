/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclaim_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:15:12 by jamerlin          #+#    #+#             */
/*   Updated: 2018/04/19 15:15:12 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../../inc/header.h"

int		name_no_event(int i, t_inp *inp, int pos)
{
	ft_putstr_fd("!: No such event: ", 2);
	find_in_his(inp, inp, &i, pos);
	custom_return();
	return (-1);
}

int		no_event(int i)
{
	ft_putstr_fd("!: No such event: ", 2);
	ft_putnbr(i);
	custom_return();
	return (-1);
}

void	fill_str(t_inp *inp, char (*str)[20])
{
	int		i;

	i = 0;
	while (inp && inp->c && inp->c >= '0' && inp->c <= '9')
	{
		(*str)[i] = inp->c;
		inp = inp->next;
		i++;
	}
}
