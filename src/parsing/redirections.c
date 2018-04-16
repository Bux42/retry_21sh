/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 08:30:44 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/16 17:44:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			not_closed(t_inpl *cp)
{
	if (cp->next && cp->next->inp->c == '-' && !cp->next->inp->next)
		return (0);
	return (1);
}

int			check_fd_aggr_left(t_inp *cp)
{
	int		type;

	type = 0;
	cp = cp->next;
	if (cp && cp->next && cp->next->c == '&')
	{
		cp = cp->next;
		if (cp->next && cp->next->c > 47 && cp->next->c < 58)
			if (!cp->next->next)
				return (type | LAGGR);
		if (!cp->next)
			return (type | LAGGRIN);
	}
	return (-1);
}

int			check_fd_aggr_right(t_inp *cp)
{
	int		type;

	type = 0;
	cp = cp->next;
	if (!cp->next)
		return (type | AGGRFILE);
	if (cp->next->c == '&')
	{
		cp = cp->next;
		if (cp->next && cp->next->c > 47 && cp->next->c < 58)
			if (!cp->next->next)
				return (type | AGGR);
		if (!cp->next)
			return (type | CLOSEAGGR);
	}
	if (cp->next->c == '>')
		if (!cp->next->next)
			return (type | AGGRFILE | ATOFILE);
	return (-1);
}
